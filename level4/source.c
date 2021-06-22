
int							main(void)
{
	// sub 0xb0
	int						stat_loc; // 0x1c
	char					buffer[0x80]; // 0x20, 128??
	int						p; // 0xa0
	pid_t					f; // 0xac

	f = fork();
	memset(buffer, 0, 0x20 * 4); // rep stos
	if (f == 0) // jne<+161>
	{
		prctl(0x1, 0x1, 0, 0, 0);
		ptrace(0, 0, 0, 0); // PTRACE_TRACEME
		puts("Give me some shellcode, k");
		gets(buffer);
		// jmp +338
	}
	else
	{
		while (1)
		{
			wait(&stat_loc);
		// WIFEXITED:
		// #define	__WTERMSIG(status)	((status) & 0x7f)
		// #define	__WIFEXITED(status)	(__WTERMSIG(status) == 0)
		// WIFSIGNALED:
		// #define __WIFSIGNALED(status)
		//  (((signed char) (((status) & 0x7f) + 1) >> 1) > 0)
			if (WIFEXITED(stat_loc) || WIFSIGNALED(stat_loc))
			{
				puts("child is exiting...");
				break ;
			}
			else
			{
				p = ptrace(0x3 ,f, 0x2c, 0x0);
				if (p == 0xb) // 11
				{
					puts("no exec() for you");
					kill(f, SIGKILL);
				}
			}
		}
	}
}
