/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:58 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:28:59 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

int	open_file(char *path, int flag, mode_t mode)
{
	int	fd;

	fd = open(path, flag, mode);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		if (!path)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(path, 2);
		if (errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", 2);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		return (-1);
	}
	return (fd);
}

int	handle_fd_in(t_node *node)
{
	t_redir	*tmp;
	int		fd_in;

	tmp = node->redirections;
	fd_in = 0;
	while (tmp)
	{
		if (tmp->tok == REDIR_IN)
		{
			if (fd_in)
				close(fd_in);
			tmp->file = expand_file(tmp->file);
			fd_in = open_file(tmp->file, O_RDONLY, 0644);
		}
		else if (tmp->tok == HEREDOC)
		{
			if (fd_in)
				close(fd_in);
			(1 && 1) && (fd_in = tmp->fd, tmp->s_fd = -1);
		}
		if (fd_in < 0)
			return (-1);
		tmp = tmp->rchild;
	}
	return (node->fd[0] = fd_in, 1);
}

int	handle_fd_out(t_node *node)
{
	t_redir	*tmp;
	int		fd_out;

	tmp = node->redirections;
	fd_out = 0;
	while (tmp)
	{
		tmp->file = expand_file(tmp->file);
		if (tmp->tok == REDIR_OUT)
		{
			if (fd_out)
				close(fd_out);
			fd_out = open_file(tmp->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (tmp->tok == REDIR_APPEND)
		{
			if (fd_out)
				close(fd_out);
			fd_out = open_file(tmp->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		if (fd_out < 0)
			return (-1);
		tmp = tmp->rchild;
	}
	return (node->fd[1] = fd_out, 1);
}

int	handle_in_out_file(t_node *node, t_var *var)
{
	if (handle_fd_in(node) < 0)
		return (var->status = 1, -1);
	if (handle_fd_out(node) < 0)
		return (var->status = 1, -1);
	if (node->fd[0] != 0)
	{
		dup2(node->fd[0], STDIN_FILENO);
		close(node->fd[0]);
	}
	if (node->fd[1] != 0)
	{
		dup2(node->fd[1], STDOUT_FILENO);
		close(node->fd[1]);
	}
	return (1);
}

int	handle_rederction(t_node *node, t_var *var)
{
	if (node->redirections)
	{
		if (handle_in_out_file(node, var) < 0)
			return (-1);
	}
	return (1);
}
