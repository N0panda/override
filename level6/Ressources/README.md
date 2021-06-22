Dans le programme level06 on va avoir la fonction <main> ainsi qu'une fonction <auth>. De plus le programme comprend un signal qui au bout d'un certain temps fait un timeout.

Le programme nous demande d'entrer un 'login' qu'il va récupérer via <fgets> ainsi qu'un Serial qu'il récupèrera avec un <scanf> :

***********************************
*               level06           *
***********************************
-> Enter Login:
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial:

Dans la fonction <auth>, la ligne suivante nous indique que le login doit être au moins de taille 7 ou plus si non la fonction <auth> ne return pas 0 et on remaque que pour avoir accès au shell nous devons faire en sorte que <auth> return 0:

0x08048786 <+62>:    cmpl   $0x5,-0xc(%ebp)

Tout d'abord pour passer  l'appel de la fonction ptrace car nous n'avons pas les droits avec gdb et donc ptrace retourne -1 on en va donc pas passé cette sécurité : 

0x080487ba <+114>:   cmp    $0xffffffff,%eax
0x080487bd <+117>:   jne    0x80487ed <auth+165>

On met donc un breakpoint au niveau du cmp et on modifie le registre $eax :
> set $eax=1

A l'instruction <165> notre login est chargé dans %eax et va être hash au niveau des instructions suivantes :

0x080487f0 <+168>:   add    $0x3,%eax
0x080487f3 <+171>:   movzbl (%eax),%eax
0x080487f6 <+174>:   movsbl %al,%eax
0x080487f9 <+177>:   xor    $0x1337,%eax
0x080487fe <+182>:   add    $0x5eeded,%eax
0x08048803 <+187>:   mov    %eax,-0x10(%ebp)

On voit que la valeur une fois transformé est stocké à $ebp - 0x10

Ces instructions suivantes nous indique que si la valeur trouvé à $ebp - 0x10 est la même que celle dans %eax a cet instant (notre Serial donné en input) alors on jump a l'instructions <+298> et la fonction <auth> retournera donc 0 ce qui lancera le shell.

On lit ce qu'il se trouve a l'adresse $ebp - 0x10 ce qui correspond a notre Login une fois le hash effectué. Par exemple "nopanda" donnera => 6233784.

0x08048866 <+286>:   cmp    -0x10(%ebp),%eax
0x08048869 <+289>:   je     0x8048872 <auth+298>
0x0804886b <+291>:   mov    $0x1,%eax
0x08048870 <+296>:   jmp    0x8048877 <auth+303>
0x08048872 <+298>:   mov    $0x0,%eax
0x08048877 <+303>:   leave
0x08048878 <+304>:   ret

> x/wx $ebp - 0x10
    0xffffd698:     0x005f1eb8

ce qui donne en décimal => 6233784

On a donc plus qu'a quitter GDB et relancer le programme avec le login précédement choisi ainsi que le Serial récupéré :

***********************************
*               level06           *
***********************************
-> Enter Login: nopanda
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6233784
Authenticated!

> cat /home/users/level07/.pass
    GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8