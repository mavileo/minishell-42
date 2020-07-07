/* // 42 HEADER

#include "minishell.h"

t_env *env = NULL;

int		main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)envp;
	(void)av;
	char *input;
//	list_token_t *l;
//	char a = 1;

	// allouer environment hash table
	init_env();

//	while (a)
//	{
		prompt();
		get_next_line(0, &input);
		// transfo input en liste de token
		//l = 
		input_to_token_list(input, NULL);
		// executer instructions
		// free liste
//		if (ft_strcmp(input, "exit") == 0) // temporaire
//			a = 0;
//	}
	free(input);
	// free environment
	free_all_env();
	return (0);
}
 */