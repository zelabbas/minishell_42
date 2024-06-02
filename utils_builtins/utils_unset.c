/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:29:20 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:29:21 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

int	is_valid(char c, int fisrt)
{
	if (fisrt == 1)
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
	else
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || c == '_');
}

int	check_var(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i] && is_valid(str[i], 1))
	{
		i++;
		len++;
	}
	while (str[i] && is_valid(str[i], 0))
		i++;
	if (!len || (str[i] && !is_valid(str[i], 0)))
	{
		errors_unset(str);
		return (false);
	}
	return (true);
}

void	delete_node(t_var *var, t_env *node, int check)
{
	t_env	*tmp;

	if (!check)
	{
		tmp = var->env;
		var->env = var->env->next;
	}
	else
	{
		tmp = node->next;
		node->next = node->next->next;
	}
	(free(tmp->env), free(tmp->var), free(tmp->content));
	(free(tmp), tmp = NULL);
}
