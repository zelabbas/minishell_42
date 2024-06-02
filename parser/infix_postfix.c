/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_postfix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:19:46 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:19:49 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	push_to_stack(t_node **head_src, t_node **head_dst)
{
	t_node	*node;
	t_node	*tmp;

	if (!head_src || !(*head_src))
		return ;
	node = *head_src;
	*head_src = (*head_src)->rchild;
	node->rchild = NULL;
	if (*head_src)
		(*head_src)->lchild = NULL;
	if (!(*head_dst))
		*head_dst = node;
	else
	{
		tmp = *head_dst;
		while (tmp->rchild)
			tmp = tmp->rchild;
		tmp->rchild = node;
		node->lchild = tmp;
	}
}

void	push_to_tok_stack(t_node **head_src, t_node **head_dst)
{
	t_node	*node;

	if (!head_src || !(*head_src))
		return ;
	node = *head_src;
	*head_src = (*head_src)->rchild;
	node->rchild = NULL;
	if (*head_src)
		(*head_src)->lchild = NULL;
	if (!(*head_dst))
		*head_dst = node;
	else
	{
		(*head_dst)->lchild = node;
		node->rchild = *head_dst;
		*head_dst = node;
	}
}

void	remove_node(t_node **head_src)
{
	t_node	*tmp;

	if (!(*head_src))
		return ;
	if (!(*head_src)->rchild)
	{
		free(*head_src);
		*head_src = NULL;
	}
	else
	{
		tmp = *head_src;
		*head_src = (*head_src)->rchild;
		(*head_src)->lchild = NULL;
		free(tmp);
	}
}

void	start_algo(t_node **head, t_node **stack_tok, t_node **new_stack)
{
	while (*head)
	{
		if ((*head)->tok == EXPR)
			push_to_stack(head, new_stack);
		else if ((*head)->tok != BRKT_OPEN && (*head)->tok != BRKT_CLOSE)
		{
			while (*stack_tok
				&& (*stack_tok)->precedence >= (*head)->precedence)
			{
				push_to_stack(stack_tok, new_stack);
			}
			push_to_tok_stack(head, stack_tok);
		}
		else if ((*head)->tok == BRKT_OPEN)
			push_to_tok_stack(head, stack_tok);
		else if ((*head)->tok == BRKT_CLOSE)
		{
			remove_node(head);
			while ((*stack_tok)->tok != BRKT_OPEN)
			{
				push_to_stack(stack_tok, new_stack);
			}
			remove_node(stack_tok);
		}
	}
}

t_node	*ft_infix_postfix(t_node **head)
{
	t_node	*stack_tok;
	t_node	*new_stack;

	stack_tok = NULL;
	new_stack = NULL;
	start_algo(head, &stack_tok, &new_stack);
	while (stack_tok)
		push_to_stack(&stack_tok, &new_stack);
	return (new_stack);
}
