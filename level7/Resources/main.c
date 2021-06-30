#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

# define P_READ  0
# define P_WRITE 1

static char					buffer[1024 + 1];
static ssize_t				buffer_size = sizeof(buffer) - 1;
static ssize_t				buffer_read;

static void					show_buffer(void)
{
	dprintf(STDERR_FILENO, "buffer content: ( %zu Bytes ) :\n%s\n", buffer_read, buffer);
}

static void					read_stdin(void)
{
	fflush(stdout);
	fflush(stdin);
	buffer_read = read(STDIN_FILENO, buffer, buffer_size);
	buffer[buffer_read] = 0;
}

static void					write_stdout(char *const format, ...)
{
	va_list					args;
	char					lbuffer[128];
	int						len;

	va_start(args, format);
	len = vsprintf(lbuffer, format, args);
	write(STDOUT_FILENO, lbuffer, (ssize_t)len);
	va_end(args);
}

static void					write_stdout_number(const int value)
{
	char					lbuffer[128];

	sprintf(lbuffer, "%d\n", value);
	write(STDOUT_FILENO, lbuffer, strlen(lbuffer));
}

static void					try_store(const int index, const int value)
{
	write_stdout_number(value);
	read_stdin();
	write_stdout_number(index);
}

int							main(int argc, char **argv, char **environ)
{
	int						pid;
	char					*prog[2];
	int						pstdin[2];
	int						pstdout[2];

	static const int		start_range = -300;
	static const int		end_range = 300;
	int						index;

	int						target_start_range = -1;
	int						target_end_range = -1;
	int						target_length = -1;
	int						ctarget_start_range = -1;
	int						ctarget_length = 0;

	if (argc != 2)
	{
		printf("usage: %s <binary>\n", *argv);
		return (1);
	}
	if (pipe(pstdin) || pipe(pstdout))
	{
		printf("%s: pipe() => %s\n", *argv, strerror(errno));
		return (1);
	}
	if (!(pid = fork()))
	{
		close(pstdin[P_WRITE]);
		close(STDIN_FILENO);
		dup(pstdin[P_READ]);
		close(pstdin[P_READ]);

		close(pstdout[P_READ]);
		close(STDOUT_FILENO);
		dup(pstdout[P_WRITE]);
		close(pstdout[P_WRITE]);

		setvbuf(stdin, NULL, _IONBF, 0);
		setvbuf(stdout, NULL, _IONBF, 0);

		prog[0] = argv[1];
		prog[1] = NULL;
		execve(prog[0], prog, environ);
		dprintf(STDERR_FILENO, "%s: execve: %s\n", *argv, strerror(errno));
	}
	else
	{
		close(pstdin[P_READ]);
		close(STDOUT_FILENO);
		dup(pstdin[P_WRITE]);
		close(pstdin[P_WRITE]);

		close(pstdout[P_WRITE]);
		close(STDIN_FILENO);
		dup(pstdout[P_READ]);
		close(pstdout[P_READ]);

		setvbuf(stdin, NULL, _IONBF, 0);
		setvbuf(stdout, NULL, _IONBF, 0);

		write_stdout("store\n");
		read_stdin();
		index = start_range;
		while (index <= end_range)
		{
			try_store(index, 42);
			write_stdout("store\n");
			read_stdin();
			if (strstr(buffer, "Completed store command successfully"))
			{
				if (ctarget_start_range == -1)
					ctarget_start_range = index;
				else
					++ctarget_length;
				dprintf(STDERR_FILENO, "> %d\n", index);
			}
			else if (strstr(buffer, "This index is reserved for wil!"))
			{
				if (ctarget_start_range != -1 && (target_length == -1 || ctarget_length > target_length))
				{
					target_start_range = ctarget_start_range;
					target_end_range = index; 
					target_length = ctarget_length;
					dprintf(STDERR_FILENO, "range(%d, %d) len:%d\n", target_start_range, target_end_range, target_length);
				}
				ctarget_start_range = -1;
				ctarget_length = 0;
				dprintf(STDERR_FILENO, "failure %d\n", index);
			}
			++index;
		}
		dprintf(STDERR_FILENO, "best range(%d, %d) len:%d\n", target_start_range, target_end_range, target_length);
		waitpid(pid, NULL, 0);
	}
	return (0);
}







