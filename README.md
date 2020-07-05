# minishell

test (compile la libft + une lib de toutes les sources indiquées du minishell) :

make minishlib

gcc main.c libft/libft.a minishlib.a

## Parsing

1. Récupère la string input.
2. Sépare aux espaces, sauf si les espaces sont entre des quotes.
3. Sépare aux opérateurs (symbols)
4. Crée une liste de tokens. Les tokens ont un type et un tableau d'arguments (str). Place les tokens dans un ordre cohérent pour l'execution.

Exemple:

    $> "cat -e|grep>file.txt '   aliens';"
    aliens in a spaceship
    ___aliens dancing
       aliens invading earth   
    [CTRL-D]
    $> cat file.txt
       aliens invading earth$
    
On voit que bash parse de manière à ce que même sans espace, les commandes soient distinguées des opérateurs, et que si l'operateur ne sépare pas les commandes, comme la redirection par exemple, les mots suivants font quand même partie de la commande.
Ici la deuxième commande est **grep**, et le mot qui suit la redirection et son fichier est considéré comme l'argument de **grep**.

1. On récupère la string :

       "cat -e|grep>file.txt '   aliens';"
2. On en fait une liste chaînée, qui contient des strings. On sépare aux espaces, sauf si les espaces sont entre des quotes.

       {"cat"} -> {"-e|grep>file.txt"} -> {"'   aliens';"} -> NULL
        
3. On redécoupe en fonction des opérateurs (symbols : >>, >, <, |, ;).

       {"cat"} -> {"-e"} -> {"|"} -> {"grep"} -> {">"} -> {"file.txt"} -> {"'   aliens'"} -> {";"} ->  NULL
        
4. Transformer cette liste en une liste de tokens, et "remettre en ordre".

       {type: COMMAND, args: ["cat", "-e", null]} ->
          {type: PIPE, args: [null]} ->
              {type: COMMAND, args: ["grep", "'   aliens'", null]} ->
                  {type: R_TRUNC, args: ["file.txt", null]} ->
                      {type: SEMICLON, args: [null]} -> NULL

## Variables d'environnement

Les variables d'environnement sont contenues dans la liste chainee t_env *env, definie comme variable globale. Chaque maillon contient le nom de la variable ainsi que sa valeur, ces deux chaines de caracteres sont allouees dynamiquement sur la heap.
Voici les differentes fonctions utiles pour manipuler les variables d'environnement

       int		add_env(char *name, char *value)
Cette fonction ajoute une variable d'environnement a la liste chainee de variables d'environnement si celle la existe deja, sinon elle la cree avant de creer le premier maillon. Retourne 1 en cas d'echec du malloc, 0 dans les autres cas.

       t_env	*get_env(char *name)
Retourne la maillon de la liste dont le nom est egal a celui passe en parametre.

       char	*get_env_value(char *name)
Retourne la valeur (sous forme de chaine de caractere) de la variable d'environnement correspondant au nom passe en parametre si une correcpondance est trouvee, ou un pointeur nul si aucune variable d'environnement n'est trouvee.

       char	*replace_env_in_str(char *str, char *res, int i)
Remplace les variables d'environnement par leurs valeur dans une chainee de caractere et retourne la chaine modifiee. Retourne la chaine originale si aucune variable d'environnement n'est trouvee allouee dynamiquement sur la heap.
Exemple : Si $USER=user42, replace_env_in_str("$USER) = user42

       int		actualise_env(char *name, char *value)
Si une variable d'environnement portant le nom passe en parametre est trouvee, sa valeur est remplacee par celle pasee en parametre.

       void	*free_env(t_env *env)
Free les deux chaines contenues dans le maillon avant de free le maillon.