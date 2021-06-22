
le programme prend un nombre, ce nombre est soustrait a la valeur 0x1337d00d, 
cette valeur est utiliser par une fonction decrypt qui xor une chaine de char: "Q}|u`sfg~sf{}|a3" a cette valeur
la fonction test appel decrypt, si la valeur est inferieur a 0x15 sinon elle appel decrypt avec un parametre aleatoire, 
on imagine donc, que reponse doit se trouver entre -infini, o & 0x15, un programme testera toute les possibiltees positive:

#include <stdio.h>

int		main(void)
{
	int	index;
	int	c;
	char	buffer[0x11];
	static const char	source[] = "Q}|u`sfg~sf{}|a3";

	for (int r = 0; r < 0x15; r++)
	{
		index = 0;
		while (index < 0x10)
		{
			buffer[index] = source[index] ^ r;
			++index;
		}
		buffer[index] = 0;
		printf("%d %s\n", r, buffer);
	}
}

$ ./a.out
0 Q}|u`sfg~sf{}|a3
1 P|}targfrgz|}`2
2 S~wbqde|qdy~c1
3 R~vcped}pex~b0
4 Uyxqdwbczwbyxe7
5 Txypevcb{vc~xyd6
6 W{zsfu`axu`}{zg5
7 Vz{rgta`yta|z{f4
8 Yut}h{nov{nsuti;
9 Xtu|izonwzortuh:
10 [wvjylmtylqwvk9
11 Zvw~kxmluxmpvwj8
12 ]qpyljkrjwqpm?
13 \pqxm~kjs~kvpql>
14 _sr{n}hip}husro=
15 ^rszo|ihq|itrsn<
16 Amlepcvwncvkmlq#
17 @lmdqbwvobwjlmp"
18 Congratulations!
19 Bnofs`utm`uhnor
20 Eihatgrsjgroihu'

on remarque que la chaine xor 18 donne Congratulation, or une fois que decrypt a appliquer la transformation il compare la chaine a congratulations pour donner une shell, donc en tirant profit de la soustraction, on peux donner au programme la valeur 18

p 0x1337d00d - 18
> 322424827

./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ ls
ls: cannot open directory .: Permission denied
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
