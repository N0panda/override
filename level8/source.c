#include <stdio.h>
#include <string.h>

void        log_wrapper(FILE *log_fd, char *string, char *file_name)
{
    char buffer[0x110];
    int len;

    strcpy(buffer, string);
    snprintf(&buffer[strlen(buffer)], 236, file_name);
    buffer[strcspn(buffer, "\n")] = '\0';
    fprintf(log_fd, "LOG: %s\n", file_name);
    return;
}

int         main(int argc, char **argv)
{
	char	c;
    FILE    *log_fd;
    FILE    *file_fd
    char    *prefix;
    char    path[0x70];

    if (argc != 2)
        printf("Usage: ./level08 filename");

    if ((log_fd = fopen("./backups/.log", 'w')) == 0)
    {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    log_wrapper(log_fd, "Starting back up: ",argv[1]);

    if ((file_fd = fopen(argv[1], 'r')) == 0)
    {
        printf("ERROR: Failed to open %s\n", argv[1])
        exit(1);
    }
    prefix = "./backups/";
    memcpy(path, prefix, strlen(prefix));

    path = strncat(path, argv[1])

    int fd;

    if ((fd = open(path, 0xc1)) == 0)
    {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
    }

    while ((c = fgetc(file_fd)) != 0x0)
        write(fd, &c, 1);
    
    log_wrapper(log_fd, "Finished back up ", argv[1]);

    fclose(file_fd);
    close(fd);

    return 0;
}
