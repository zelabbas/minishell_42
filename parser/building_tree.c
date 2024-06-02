/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:19:14 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:19:17 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

// Recursively transforms a binary tree according to specified conditions.
t_node	*ft_tree(t_node *head)
{
	if (!head)
		return (NULL);
	else if (head->tok == EXPR)
	{
		if (head->lchild && head->rchild)
		{
			head->rchild->lchild = head->lchild;
			head->lchild->rchild = head->rchild;
			if (head->rchild->rchild)
				head->lchild->rchild = head->rchild->rchild;
		}
		head->lchild = NULL;
		head->rchild = NULL;
	}
	else
	{
		head->rchild = ft_tree(head->lchild);
		head->lchild = ft_tree(head->lchild);
	}
	return (head);
}

/* Builds a binary tree from a postfix expression
represented as a double-linked list.*/
void	ft_build_tree(t_node *head)
{
	while (head->rchild)
		head = head->rchild;
	ft_tree(head);
}
