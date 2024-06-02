/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:26:48 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:26:50 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

// free the list that contain all env
void	free_node(t_env *node)
{
	free(node->env);
	free(node->var);
	free(node->content);
	node = NULL;
}

void	free_list_env(t_var *var)
{
	t_env	*head;
	t_env	*tmp;

	head = var->env;
	while (head)
	{
		tmp = head;
		free_node(tmp);
		head = head->next;
	}
}
