/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:28 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:28:29 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	ft_and(t_node *root, t_var *var)
{
	execution(root->lchild, var);
	if (!var->status)
		return (execution(root->rchild, var));
}

void	ft_or(t_node *root, t_var *var)
{
	execution(root->lchild, var);
	if (var->status)
		return (execution(root->rchild, var));
}

void	ft_pipe(t_node *root, t_var *var)
{
	int		tab[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		status;

	if (!check_pipe(tab))
	{
		var->status = 1;
		return ;
	}
	pid_1 = child_write(root->lchild, tab, var);
	if (pid_1 < 0)
		return ;
	pid_2 = child_read(root->rchild, tab, var);
	if (pid_2 < 0)
		return ;
	close(tab[1]);
	close(tab[0]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
	var->status = update_status(status);
}

void	execution(t_node *root, t_var *var)
{
	if (!root)
		return ;
	if (root->tok == AND)
		return (ft_and(root, var));
	else if (root->tok == OR)
		return (ft_or(root, var));
	else if (root->tok == PIPE)
		return (ft_pipe(root, var));
	else if (root->tok == EXPR)
		return (exec_cmd(root, var));
}
