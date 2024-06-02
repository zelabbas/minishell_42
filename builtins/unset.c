/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:08 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:28:09 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	handle_unset(t_var *var, char *tmp, t_env *list, t_env *save)
{
	int	check;

	if (!check_var(tmp))
	{
		var->status = 1;
		return ;
	}
	list = var->env;
	check = 0;
	while (list)
	{
		if (!ft_strcmp(list->var, tmp))
		{
			delete_node(var, save, check);
			break ;
		}
		save = list;
		list = list->next;
		check++;
	}
	var->status = 0;
}

void	ft_unset(t_var *var, char **cmd)
{
	char	**tmp;
	t_env	*list;
	t_env	*save;

	list = NULL;
	save = NULL;
	tmp = cmd;
	while (*++tmp)
	{
		handle_unset(var, *tmp, list, save);
	}
}
