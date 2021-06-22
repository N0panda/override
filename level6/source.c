
static int				auth(char *buffer, unsigned int input)
{
	int					len; // -0xc(ebp)
	int					v; // -0x10(ebp)
	int					index; // -0x14(ebp)

	buffer[strcspn(buffer, "\n")] = 0;
	len = strnlen(buffer, 0x20);
	if (len < 0x5) // jg
		return (1);

	if (ptrace(0x0, 0x0, 0x1, 0x0) == -1) // 0xffffffff
	{
		puts("\033[32m.---------------------------.");
		puts("\033[31m| !! TAMPERING DETECTED !!  |");
		puts("\033[32m'---------------------------'");
		return (1);
	}

	v = (buffer[3] ^ 0x1337) + 0x5eeded;
	index = 0;
	while (index < len)
	{
		if (buffer[index] > 0x1f && 
			return (-1);
		v += ((((v ^ buffer[index]) >> 0xa) * 0x539) - 0x88233b2b);
		++index;
	}
	if (input != v)
		retun (1);
	return (0);
}

int						main(void)
{
	// sub 0x50
	unsigned int		serial_input; // 0x4(esp)
	char				buffer[0x20]; // 0x2c(esp)
	
	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(buffer, 0x20, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &serial_input);
	if (auth(buffer, serial_input) == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
		return (0);
	}
	return (1);
}

