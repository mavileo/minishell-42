#include "minishell.h"

/*
**	allocd and assignd int pointer with the given value
*/

int		*aaintptr(int v)
{
	int *a;

	if ((a = malloc(sizeof(int))) == NULL)
		return (NULL);
	*a = v;
	return (a);
}

void	handle_ctrl_c(int i)
{
	t_list *plst;
	int		pid;
	(void)i;

	plst = process_pids;
	while (plst)
	{
		pid = *((int *)plst->content);
		kill(pid, SIGKILL);
		plst = plst->next;
	}
	write(1, "\n", 1);
	if (process_pids == NULL)
		prompt();
	add_env("PIPESTATUS", "130");
}

void	handle_ctrl_bs(int i)
{
	t_list *plst;
	int		pid;
	(void)i;

	plst = process_pids;
	if (plst)
		ft_putstr("Quit (core dumped)\n");
	else
		ft_putstr("\b\b  \b\b");
	while (plst)
	{
		pid = *((int *)plst->content);
		kill(pid, SIGKILL);
		plst = plst->next;
	}
}

void	save_process_pid(int pid)
{
	ft_lstadd_back(&process_pids, ft_lstnew(aaintptr(pid)));
}
