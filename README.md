# minishell

The goal of the project is to code a shell as well as some builtins (cd, pwd, echo, env, export, unset, exit). If the command typed is a builtin, it will run our implementation of this function, otherwise it will look for the corresponding executable in the directories contained in the PATH environment variable. The environment variables are imported when the program is executed, they are those of the shell in which the program was executed.

To test the shell, run the `make` command to generate the executable then execute it with the command `./minishell`.

## Parsing

1. Retrieves the string input.
2. Separates to spaces, unless spaces are between quotes.
3. Separates to operators (symbols)
4. Creates a list of tokens. Tokens have a type and an array of arguments (str). Places the tokens in a consistent order for execution.

Example:

    $> "cat -e|grep>file.txt ' aliens';"
    aliens in a spaceship
    ___aliens dancing
       aliens invading earth   
    [CTRL-D]
    $> cat file.txt
       aliens invading earth$
    
We can see that bash parse so that even without space, commands are distinguished from operators, and that if the operator does not separate commands, such as redirection for example, the following words are still part of the command.
Here the second command is **grep**, and the word following the redirection and its file is considered the argument to **grep**.

1. We retrieve the string :

       "cat -e|grep>file.txt ' aliens';"
2. We make a chained list, which contains strings. Separate by spaces, unless the spaces are between quotes.

       {"cat"} -> {"-e|grep>file.txt"} -> {"' aliens';"} -> NULL
        
3. We re-cut according to the operators (symbols: >>, >, <, |, ;).

       {"cat"} -> {"-e"} -> {"|"} -> {"grep"} -> {">"} -> {"file.txt"} -> {"' aliens'"} -> {";"} -> NULL
        
4. Transform this list into a list of tokens, and "tidy it up".

       {type: COMMAND, args: ["cat", "-e", null]} ->
          {type: PIPE, args: [null]} ->
              {type: COMMAND, args: ["grep", "' aliens'", null]} ->
                  {type: R_TRUNC, args: ["file.txt", null]} ->
                      {type: SEMICLON, args: [null]} -> NULL

## Environment variables

Environment variables are contained in the t_env *env chain list, defined as a global variable. Each link contains the name of the variable as well as its value, these two strings are dynamically allocated on the heap.
Here are the different functions useful to manipulate environment variables

       int add_env(char *name, char *value)
This function adds an environment variable to the chained list of environment variables if it already exists, otherwise it creates it before creating the first link. Returns 1 if the malloc fails, 0 in other cases.

       t_env *get_env(char *name)
Returns the link of the list whose name is equal to the one passed in parameter.

       char *get_env_value(char *name)
Returns the value (as a string) of the environment variable corresponding to the name passed as parameter if a match is found, or a null pointer if no environment variable is found.

       char *replace_env_in_str(char *str, char *res, int i)
Replaces environment variables with their values in a string and returns the modified string. Returns the original string if no environment variable is found dynamically allocated on the heap.
Example: If $USER=user42, replace_env_in_str("$USER") = user42

       int update_env(char *name, char *value)
If an environment variable with the name passed as a parameter is found, its value is replaced by the one passed as a parameter.

       void *free_env(t_env *env)
Free the two chains contained in the link before freeing the link.
