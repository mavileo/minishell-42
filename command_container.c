// 42 HEADER

#include "minishell.h"

// ne compile pas : "sequelette" seulement

// todo: typedef sur ce type de pointeurs
// tableau de pointeurs sur fonctions qui contient toutes les fonctions associé
// à chaques tokens

int		command_container(t_list *tokens_list)
{
	t_token *start;
	int return_value;
	int status;

	start = get_next_token(tokens_list);
	return_value = g_exec_token[start->type](start); // tableau de pointeurs sur fonctions

	waitpid(-1, &status, 0); // à revoir
	// si la dernière commande est un builtin
		// add_env : return_value
	// si la dernière commande n'est pas un builtin
		// add_env : WEXITSTATUS(status)
	return (0);
}
