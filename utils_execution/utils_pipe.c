/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:29:30 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:29:31 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

pid_t	child_write(t_node *node, int tab[2], t_var *var)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("bash: faild to creat child\n", 2);
		return (var->status = 1, -1);
	}
	if (pid == 0)
	{
		close(tab[0]);
		dup2(tab[1], STDOUT_FILENO);
		close(tab[1]);
		execution(node, var);
		exit(var->status);
	}
	return (pid);
}

pid_t	child_read(t_node *node, int tab[2], t_var *var)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("bash: faild to creat child\n", 2);
		return (var->status = 1, -1);
	}
	if (pid == 0)
	{
		close(tab[1]);
		dup2(tab[0], STDIN_FILENO);
		close(tab[0]);
		execution(node, var);
		exit(var->status);
	}
	return (pid);
}
