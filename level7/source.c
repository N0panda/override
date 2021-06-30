
void				clear_stdin(void)
{
	char			x;

	x = 0;
	while (42)
	{
		x = getchar();
		if (x == '\n' || x == EOF)
			break;
	}
}

static int			get_unum(void)
{
	unsigned int	r;

	fflush(stdout);
	scanf("%u", &r);
	clear_stdin();
	return r;
}

static void			read_number(int *array/* -0xc(%ebp) */)
{
	// sub 0x28
	int				index; // -0xc(ebp)

	printf(" Index: ");
	index = get_unum();
	// shl    $0x2,%eax ? 
	printf(" Number at data[%u] is %u\n", index, *(array + value));
}

static int			store_number(int *array)
{
	// sub 0x28
	int				value; // -0x10(%ebp)
	int				index; // -0xc(%ebp)

	value = 0;
	index = 0;
	printf(" Number: ");
	value = get_unum();
	printf(" Index: ");
	index = get_unum();

/** mov    $0xaaaaaaab,%edx
	mov    %ecx,%eax
	mul    %edx
	shr    %edx
	mov    %edx,%eax
	add    %eax,%eax
	add    %edx,%eax
	mov    %ecx,%edx
	sub    %eax,%edx
	test   %edx,%edx  == %3
**/ /* || */
	if (index % 3 && (index >> 0x18) == 0xb7)
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	array[index] = value;
	return (0);
}

int					main(int argc, char **argv, char **env)
{
	// sub 0x1d0
	int				value; // 0x1b4(%esp)
	char			command[0x20] = {0}; // 0x1b8(%esp) size:movl 0x0(6 * 4)
	int				array[0x64] = {0}; // 0x24(%esp) size:100

	value = 0;
	for (; *argv; ++argv)
		memset(*argv, 0, strlen(*argv));
	for (; *env; ++env)
		memset(*env, 0, strlen(*env));

	printf("----------------------------------------------------\n" \
		"  Welcome to wil's crappy number storage service!   \n" \
		"----------------------------------------------------\n" \
		" Commands:                                          \n" \
		"    store - store a number into the data storage    \n" \
		"    read  - read a number from the data storage     \n" \
		"    quit  - exit the program                        \n" \
		"----------------------------------------------------\n" \
		"   wil has reserved some storage :>                 \n" \
		"----------------------------------------------------\n\n");

	while (1)
	{
		printf("Input command: ");
		res = 1;
		fgets(command, 0x64, stdin);
		command[strlen(command) - 1] = 0x0; // movb   $0x0,0x1b8(%esp,%eax,1)

		// repz cmpsb %es:(%edi),%ds:(%esi)
		if(!strncmp(cmd, "store", 0x5))
			res = store_number(data);
		else if(!strncmp(cmd, "read", 0x4))
			res = read_number(data);
		else if(!strncmp(cmd, "quit", 0x4))
			break ; // <main+684>

		if (res == 0)
			printf(" Completed %s command successfully\n", cmd);
		else
			printf(" Failed to do %s command\n", cmd);
	}
	// <__stack_chk_fail@plt>
	return (0);
}
