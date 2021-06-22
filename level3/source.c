
static void				clear_stdin(void)
{
	char				c;

	do {
		c = getchar();
	}
	while (c != 0xa) // \n
}

static void				prog_timeout(void)
{
	__asm__("");
}

static void				get_unum(unsigned int *value)
{
	// sub 0x28

	*value = 0;
	fflush(stdout);
	scanf("%u", value);
	clear_stdin();
}

static void				decrypt(int value)
{
	// sub 0x40
	char				buffer[0x11]; // -0x1d "Q}|u`sfg~sf{}|a3"
	int					length; // -0x24
	int					index; // ins inlined

	*((int*)buffer) = 0x757c7d51;
	*((int*)buffer + 1) = 0x67667360;
	*((int*)buffer + 2) = 0x7b66737e;
	*((int*)buffer + 3) = 0x33617c7d;
	buffer[0x10] = 0x0;
	index = 0;
	length = strlen(buffer);
	while (index < length)
	{
		buffer[i] ^= value;
		++index;
	}
	if (strcmp("Congratulations!", buffer) == 0)
		system("/bin/sh");
	else
		puts("\nInvalid Password");
	// __stack_chk_fail
}

static void				test(int p, int value)
{
	// sub 0x28
	int					n; // -0xc

	n = p - value;
	if (n < 0x15)
	{
		p <<= 2; // 0x2,%eax
		p += 0x80489f0;
		decrypt(n);
	}
	else	
		decrypt(rand());
}

int						main(void)
{
	// sub 0x20
	int		value; // -0x1c, 0xffffd6dc

	srand(time(NULL));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &value); // __isoc99_scanf
	test(0x1337d00d, value);
}
