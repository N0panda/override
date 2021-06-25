
struct					data
{
	char				message[0x8c]; // 140
	char				username[0x28]; // 40
	int					message_length;
};

static void				secret_backdoor(void)
{
	// add    $0xffffffffffffff80,%rsp
	char				buffer[0x80]; // -0x80(%rbp) size:128

	fgets(stdin, 0x80, buffer);
	system(buffer);
}

static void				set_username(struct *data)
{
	// sub 0xa0
	int					index; // -0x4(%rbp)
	char				name[0x80]; // -0x90(%rbp) size:128

	// mov    %rdi,-0x98(%rbp) "\n"
	memset(name, 0, 0x10 * 8); // 16 * 8 => 0x80(128)
	puts(">: Enter your username");
	printf(">>: ");
	fgets(stdin, 0x80, name);
	index = 0; // movl   $0x0,-0x4(%rbp)
	while (index < 0x28 /* 40 */ && name[index])
	{
		data->username[index] = name[index]; // movzbl -0x90(%rbp,%rax,1),%ecx
		++index;
	}
	printf(">: Welcome, %s", data->username);
}

static void				set_msg(struct *data)
{
	// sub 0x410
	char				buffer[0x400]; // -0x400(%rbp) size:1024

	memset(buffer, 0, 0x80 * 8); // 512(0x200)
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(stdin, buffer, 0x400);
	strncpy(data->message, buffer, 0x400);
}

static void				handle_msg(void)
{
	// sub 0xc0, 192
	struct data			data; // -0xc0(%rbp)

	memset(data.message, 0, 8 * 5); // 140
 	data.message_length = 0x8c; //140; movl $0x8c,-0xc(%rbp)
	set_username(&data);
	set_msg(&data);
	puts(">: Msg sent!");
}

int						main(void)
{
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------");
	handle_msg();
	return (0);
}
