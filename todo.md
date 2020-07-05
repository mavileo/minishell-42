# TODO

|            A FAIRE                   |           EN COURS          | A TESTER      | FINI |
| ------------------------------------ | --------------------------- | ------------- | ---- |
| replacer printf par ft_printf        | conception: execution liste | builtins      |      |
| normer                               |                             | expands       |      |
| $PATH dans init_env()                |                             | syntax errors |      |
|                                      |                             | escape        |      |
|                                      |                             |               |      |


# execution liste : idée 1

### à prendre en compte :

- plusieurs processus peuvent tourner en même temps, et se finir dans un ordre différent de l'ordre de lancement, donc on doit d'abord faire autant de forks que nécéssaires PUIS wait(). (voir waitpid(-1), c'est censé attendre tout les processus fils par défaut.)
- dans le cas d'une redirection : on doit transformer la sortie standard en un file descriptor au fichier correspondant. après que le processus fils ai été lancé, on doit restorer la sortie standard (dont on la save avant).
- dans le cas d'une pipeline, un pipe doit être close dès que son deuxieme processus à été lancé, sinon le pipeline ne fonctionne pas (boucle infinie).
- les builtins ne sont pas lancé avec fork(), donc il faudra les différencier. Et on ne récupère par leur valeur de retour avec WEXITSTATUS sinon la valeur est fausse, donc à gérer.

### todo

Faire une fonction qui sert de 'container' pour une commande.

Exemple :

    $> ls | grep truc | cut -c1-5 >> file.md ; clear ; cat file.md
    
Ca se découpe en trois commandes. A chaque ';' (SEMICOLON) on envoie dans la fonction qui sert de container.
Cette fonction s'occuperai de lancer l'execution de la liste, puis d'attendre que les processus fils se terminent, récupérer la valeure de retour finale, et mettre à jour la variable d'environnement PIPESTATUS.


Ensuite, il y aurai  une fonction associée à chaque type de token.


On pourrait tout simplement appeler la fonction associé sur chaque token dans l'ordre de la liste. Donc sans 'tri'.


Chacunes de ses fonctions aurait une responsabilité supplémentaire, qui serait de vérifier si un token de plus haute priorité suit le token actuellement traité.


Si c'est le cas, la fonction appel la fonction correspondante sur le token trouvé, et ne poursuit pas son execution.


Responsabilités de chaques fonctions :

COMMAND :
  - chercher le path absolu de l'executable
  - fork()
  - child process : vérifier si le processus doit lire ou écrire sur un autre fd que STDIN ou STDOUT, exit en cas d'erreur, etc
