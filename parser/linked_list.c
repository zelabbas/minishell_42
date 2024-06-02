/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:20:00 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:20:01 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

// create a command node.
t_node	*ft_create_cmd(char *str, int len, t_token tok, t_redir *redlist)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	(void)len;
	if (!new)
		allocate_error(strerror(errno));
	new->pre_cmd = str;
	new->cmd = NULL;
	new->redirections = NULL;
	new->tok = tok;
	new->precedence = ft_precedence(tok);
	if (tok == EXPR)
		new->redirections = redlist;
	new->rchild = NULL;
	new->lchild = NULL;
	return (new);
}

// Add a command node to the end of a linked list
int	ft_add_back(t_node **head, t_node *new)
{
	t_node	*tmp;

	if (!new)
		return (-1);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->rchild)
			tmp = tmp->rchild;
		tmp->rchild = new;
		new->lchild = tmp;
	}
	return (1);
}

// create a redirection node
t_redir	*ft_create_rednode(char *file_name, t_token tok)
{
	t_redir	*rednode;

	rednode = (t_redir *)malloc(sizeof(t_redir));
	if (!rednode)
		return (NULL);
	rednode->file = file_name;
	rednode->tok = tok;
	rednode->s_fd = -1;
	rednode->lchild = NULL;
	rednode->rchild = NULL;
	return (rednode);
}

// Add a redirection node to the end of a linked list
int	ft_add_red(t_redir **redhead, t_redir *rednode)
{
	t_redir	*tmp;

	if (!rednode)
		return (-1);
	if (!*redhead)
		*redhead = rednode;
	else
	{
		tmp = *redhead;
		while (tmp->rchild)
			tmp = tmp->rchild;
		tmp->rchild = rednode;
		rednode->lchild = tmp;
	}
	return (0);
}
