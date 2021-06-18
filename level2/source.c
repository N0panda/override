// eip: "\xa8\xe5\xff\xff\xff\x7f" -> __libc_start_main+237
int				main(void)
{
	// sub 0x120
	FILE		*f; // -0x8
	size_t		r; // -0xc, 0x7fffffffe594
	char		buffer[0x60] = // -0x70, 0x7fffffffe530
	// 0x00 00 7f ff ff ff e5 00
	// 00 e5 ff ff ff 7f 00 00
	char		obuffer[0x28]; // -0xa0, 0x7fffffffe500
	char		tbuffer[0x60]; // -0x110, 0x7fffffffe490

	memset(buffer, 0, 0x60); // 0xc * 8=> 64 bits
	memset(obuffer, 0, 0x28); // 0x5 * 8
	memset(tbuffer, 0, 0x60); // 0xc * 8
	if (!(f = fopen("/home/users/level03/.pass", "r")))
	{ // jne <+210>
		r = fread(obuffer, 0x29, 1, f);
		obuffer[strcspn(obuffer, "\n")] = 0;
		// ex strcspn("toto\n", "\n") => 4
		if (r != 0x29)
		{
			fwrite("ERROR: failed to read password file\n", 0x24, 0x1, stderr);
			exit(1);
		}
		close(f);
		puts("===== [ Secure Access System v1.0 ] =====");
		puts("/***************************************\\");
		puts("| You must login to access this system. |");
		puts("/***************************************\\");
		printf("--[ Username: ");
		fgets(buffer, 0x64, stdin);
		buffer[strcspn(buffer, "\n")] = 0;
		printf("--[ Password: ");
		fgets(tbuffer, 0x64, stdin);
		buffer[strcspn(buffer, "\n")] = 0;
		puts("*****************************************");
		if (strncmp(tbuffer, obuffer, 0x29) == 0)
		{
			printf("Greetings, %s!\n", buffer);
			system("/bin/sh"); // 0x0000000000400a85
		}
		else
		{
			printf(buffer);
			puts(" does not have access!");
			exit(1);
		}
	}
	else
	{
		fwrite("ERROR: failed to open password file\n", 0x24, 0x1, stderr);
		exit(1);
	}
	
}

