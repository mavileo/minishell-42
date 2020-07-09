// 42 HEADER

#include "minishell.h"

// ne compile pas : "sequelette" seulement

// tableau de pointeurs sur fonctions qui contient toutes les fonctions associé
// à chaques tokens : mettre les bons noms

static t_exec_token_function 	g_exec_token[10] = {
	//commandenormale, //pipes, //etc
}

int		command_container(t_list *tokens_list)
{
	t_token *start;
	t_rw	rw;
	int return_value;
	int status;

	// init temporaire
	rw->fd1r = -1;
	rw->fd1w = -1;
	rw->fd2r = -1;
	rw->fd2w = -1;
	start = get_next_token(tokens_list);
	return_value = g_exec_token[start->type](start, &rw); // tableau de pointeurs sur fonctions

	waitpid(-1, &status, 0); // à revoir
	// si la dernière commande est un builtin
		// add_env : return_value
	// si la dernière commande n'est pas un builtin
		// add_env : WEXITSTATUS(status)
	return (0);
}
