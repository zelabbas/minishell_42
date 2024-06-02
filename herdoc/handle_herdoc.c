/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:30:30 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:30:31 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	_search_herdoc_(t_node *node, t_var *var)
{
	handle_herdoc(node->lchild, var);
	handle_herdoc(node->rchild, var);
}

void	_herdoc_(t_node *node, t_var *var)
{
	t_redir	*tmp;

	if (node->redirections)
	{
		tmp = node->redirections;
		while (tmp)
		{
			if (tmp->tok == HEREDOC)
			{
				tmp->fd = ft_heredoc(tmp, var);
				if (tmp->fd == -1)
					var->status = 1;
			}
			tmp = tmp->rchild;
		}
	}
}

void	handle_herdoc(t_node *root, t_var *var)
{
	if (!root)
		return ;
	if (root->tok != EXPR)
		return (_search_herdoc_(root, var));
	else if (root->tok == EXPR)
		return (_herdoc_(root, var));
}
