/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:27:50 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:27:51 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

// check if there's the path that contain env 
int	check_path(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], "/usr/bin"))
			return (1);
	}
	return (0);
}

// display all env that they have the content
void	ft_env(t_var *var)
{
	t_env	*tmp;
	char	**tab;

	tab = get_paths(var);
	if (!tab || !check_path(tab))
	{
		ft_putstr_fd("bash: env: is a directory\n", 2);
		free_matrix(tab);
		var->status = 126;
		return ;
	}
	tmp = var->env;
	while (tmp)
	{
		if ((!ft_strcmp(tmp->var, "PATH") && var->flag)
			|| find_char(tmp->env, '=') == -1)
		{
			tmp = tmp->next;
			continue ;
		}
		printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
	free_matrix(tab);
	var->status = 0;
}
