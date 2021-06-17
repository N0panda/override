Lorsqu'on lance le programme ./level00 on nous demande un mot de passe : 

-------------------------------------------------------------

***********************************
*            -Level00 -           *
***********************************
Password:

--------------------------------------------------------------

On lit l'asm du programme avec gdb :

    -> 0x080484de <+74>:    call   0x80483d0 <__isoc99_scanf@plt> :
scanf récupère la ligne envoyé sur l'entrée standard et la met dans le registre $eax
    -> 0x080484e7 <+83>:    cmp    $0x149c,%eax :
Compare ce qu'on a envoyé avec 0x149c ce qui donne '5276' en décimal
    -> 0x080484ec <+88>:    jne    0x804850d <main+121>
Si on envoit 5276 on ne jump pas et ensuite system("/bin/sh") est appelé.

On a donc notre mot de passe : 5276

> cat /home/users/level01/.pass
    uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
