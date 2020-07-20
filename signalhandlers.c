#include "minishell.h"

void	handle_ctrl_c(int i)
{
	printf("CTRL-C has been pressed. Param: %d\n", i);
}

void	handle_ctrl_bs(int i)
{
	printf("CTRL-\\ has been pressed. Param: %d\n", i);
}
