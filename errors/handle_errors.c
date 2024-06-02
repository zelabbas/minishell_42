/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:20 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:28:21 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

int	check_pipe(int tab[2])
{
	if (pipe(tab) == -1)
	{
		ft_putstr_fd("bash: faild to creat the pipe!\n", 2);
		return (0);
	}
	return (1);
}

void	errors_export(char *s)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("` :not a valid identifier\n", 2);
}

void	errors_unset(char *s)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("` :not a valid identifier\n", 2);
}

void	error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	error_execve(char *path, int error)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" :", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (error == ENOENT)
		exit(127);
	if (error == EACCES)
		exit(126);
}
