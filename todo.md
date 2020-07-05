# TODO

|            A FAIRE                   |           EN COURS          | A TESTER      | FINI |
| ------------------------------------ | --------------------------- | ------------- | ---- |
| replacer printf par ft_printf        | conception: execution liste | builtins      |      |
| normer                               | struct : file descriptors   | expands       |      |
| $PATH dans init_env()                |                             | syntax errors |      |
| get_path()                           |                             | escape        |      |
| fonction container                   |                             |               |      |
| def règles write/read pr processus   |                             |               |      |
| get_next_token()                     |                             |               |      |
| exec COMMAND                         |                             |               |      |
| exec REDIRECTION                     |                             |               |      |
| exec PIPE                            |                             |               |      |
| exec SEMICOLON                       |                             |               |      |
| conception: signaux                  |                             |               |      |
| bonus: ET et OU                      |                             |               |      |



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

**A décider :**

Si les fonctions vérifient qu'un token plus haut existe ou non avant de poursuivre leur executions, pour qu'au final les fonctions de tokens de plus haute priorité finissent par rappeler cette même fonction sur ces mêmes tokens plus tard, on fais des appels de fonctions inutils à certains moment.

Concrètement : si un une fonction COMMAND est appelé, puis arrête son execution pour appeler une fonction PIPE sur un token de ce même type, qui finira par rappeler la fonction COMMAND sur le token de ce même type situé à gauche, voir celui situé à droite, on commence par COMMAND pour rien.

Peut être que c'est mieux si on commencer par appeler get_next_token(), qui nous renverrait un pipe (pour continuer avec le même exemple), puis appeler la fonction correspondante, qui appelera la fonction COMMAND au bon moment.

### Responsabilités de chaques fonctions :

**COMMAND** :
  - vérifier si un token de plus haute priorité suit
  - déterminer si l'executable est un executable ou bien un BUILTIN
  - chercher le path absolu de l'executable
  - fork()
  - child process : 
    - vérifier si le processus doit lire ou écrire sur un autre fd que STDIN ou STDOUT
    - transformer STDIN_FILNO ou STDOUT_FILENO en un nouveau file descriptor correspondant au fichier ouvert (fonction : dup2())
    - execve()
    - exit en cas d'erreur, etc
  
**REDIRECTION** : (à confirmer)
  - vérifier si un token de plus haute priorité suit ? (est ce que get_next_token() renvoit déjà le plus haut ?)
  - si la redirection est R_IN ('<') : render error si le fichier passé en argument n'existe pas ou n'est pas écrivable
  - stocker le file descriptor obtenu dans le bon ednroit de la structure (structure file descriptors en cours + règle de write/read)
  - executer le processus à gauche (le token à gauche) en appelant la fonction COMMAND (exec_command() ? mettre à jour les noms plus tard)
  
Notes :
 
Si les file descriptors sur lesquels un processus doit lire et/ou écrire sont stockés qqpart, et que la transformation (fonction: dup2()) se passe dans le processus fils une fois que celui ci a été fork(), alors, pas besoin ni de sauvegarder STDIN et STDOUT ni de les restorer. (à confirmer)
  
**PIPE** : (à confirmer)
 - vérifier si un token de plus haute priorité suit ? (est ce que get_next_token() renvoit déjà le plus haut ?)
 - créer un pipe (fonction: pipe())
 - stocker les file descriptors
 - executer le processus de gauche (attention: il faut que ça marche même si à gauche se trouve un token REDIRECTION)
 - fermer le pipe précedent ? (pas celui qui vient d'être créer, celui qui est stocké dans la struct)
 - executer le processus de droite OU appeler la fonction PIPE sur le prochain token PIPE (pipeline)
 - fermer le pipe créer lors de cette fonction
 
 **SEMICOLON** :
   - est la plus haute priorité !
   - tout se qui se trouve à gauche de ce token doit être découpé en une nouvelle liste et être envoyé dans la fonction container pour être executé
   - si il y'as un autre semicolon plus loin, on appel la fonction semicolon sur ce token qui se trouve plus loin
   - si il n'ya pas d'autre semicolon plus loin, tout se qui se trouve à droite du token doit être envoyé dans la fonction container, etc.
   
 **AND** : (bonus)
   - possède la même priorité que OU, la règle de priorité à appliquer est la suivante : https://unix.stackexchange.com/questions/88850/precedence-of-the-shell-logical-operators
   - opère de la même manière que semicolon à part que : n'execute ce qui se trouve à droite que si fonction container sur la partie gauche à renvoyé une valeur de zéro.
   
**OU** : (bonus)
  - n'execute ce qui se trouve à droite que si ce qui se trouve à gauche à renvoyé une valeur différente de zéro.
