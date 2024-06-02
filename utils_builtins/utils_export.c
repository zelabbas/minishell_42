/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:29:15 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 17:35:23 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

t_env	*copy(t_var *var)
{
	t_env	*tmp;
	t_env	*list_env;

	list_env = NULL;
	tmp = var->env;
	while (tmp)
	{
		ft_add_env(&list_env, ft_creat_env_exp(tmp->env,
				ft_strdup(tmp->var), ft_strdup(tmp->content)));
		tmp = tmp->next;
	}
	return (list_env);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->content);
		free(tmp->var);
		free(tmp->env);
		free(tmp);
		tmp = NULL;
	}
}

void	displaye_env(t_var *var)
{
	t_env	*copy_env;
	t_env	*tmp;

	copy_env = copy(var);
	sort_env(copy_env);
	tmp = copy_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, "PATH") && var->flag)
		{
			tmp = tmp->next;
			continue ;
		}
		if (find_char(tmp->env, '=') < 0)
			printf("declare -x %s\n", tmp->env);
		else
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->content);
		tmp = tmp->next;
	}
	free_env(copy_env);
	var->status = 0;
}

void	ft_switch(t_env *trav, t_env *env)
{
	char	*str;

	str = env->env;
	env->env = trav->env;
	trav->env = str;
	str = env->var;
	env->var = trav->var;
	trav->var = str;
	str = env->content;
	env->content = trav->content;
	trav->content = str;
}

void	sort_env(t_env *env)
{
	t_env	*trav;

	while (env)
	{
		trav = env->next;
		while (trav)
		{
			if (ft_strcmp(trav->var, env->var) < 0)
				ft_switch(trav, env);
			trav = trav->next;
		}
		env = env->next;
	}
}
