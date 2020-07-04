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
