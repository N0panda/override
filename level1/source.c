
static char			a_user_name[0x100];

static int			verify_user_name(void)
{
	puts("verifying username....\n");
	return memcmp(a_user_name, "dat_wil");
}

static int			verify_user_pass(char *buffer)
{
	return memcmp(buffer, "admin");
}

int					main(void)
{
	char			buffer[0x64];

	memset(buffer, 0, 0x64);
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(stdin, 0x100, a_user_name);
	if (verify_user_name())
	{
		puts("nope, incorrect username...\n");
		return (1);
	}
	puts("Enter Password: ");
	fgets(stdin, 0x64, buffer);
	if (verify_user_pass(buffer))
	{
		puts("nope, incorrect password...\n");
		return (1);
	}
	system("/bin/sh");
}
