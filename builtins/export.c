/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:02 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 17:35:59 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

bool	check_str_exp(char *s, t_var *var, int *index)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s[i] && is_valid(s[i], 1))
	{
		i++;
		len++;
	}
	while (s[i] && is_valid(s[i], 0))
		i++;
	if (!len || (s[i] && s[i] != '=' && (s[i] != '+' || s[i + 1] != '=')))
	{
		errors_export(s);
		var->status = 1;
		return (false);
	}
	*index = i;
	return (true);
}

void	handle_list_env(t_env *env, char *str, int i)
{
	char	*save_join;
	char	*save;

	if (str[i] == '+')
	{
		free(env->env);
		save = env->content;
		env->content = ft_strjoin(save, str + (i + 2));
		save_join = ft_strjoin(env->var, "=");
		env->env = ft_strjoin(save_join, env->content);
		(free(save), free(save_join));
	}
	else if (str[i] == '=')
	{
		free(env->content);
		free(env->env);
		env->content = ft_strdup(str + (i + 1));
		save_join = ft_strjoin(env->var, "=");
		env->env = ft_strjoin(save_join, env->content);
		free(save_join);
	}
}

int	is_existe(t_env *env, char *var_env, char *str, int i)
{
	while (env)
	{
		if (!ft_strcmp(env->var, var_env))
		{
			handle_list_env(env, str, i);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	add_var_to_list(t_env *env, char *var_env, char *str, int i)
{
	char	*env_join;
	char	*content;
	char	*save;

	if (!str[i])
	{
		ft_add_env(&env, ft_creat_env(var_env, var_env, ft_strdup("")));
		return ;
	}
	if (str[i] == '+')
	{
		content = ft_strdup(str + (i + 2));
		save = ft_strjoin(var_env, "=");
		env_join = ft_strjoin(save, content);
		ft_add_env(&env, ft_creat_env(env_join, var_env, content));
		(free(save), free(env_join));
	}
	else if (str[i] == '=')
	{
		content = ft_strdup(str + (i + 1));
		save = ft_strjoin(var_env, "=");
		env_join = ft_strjoin(save, content);
		ft_add_env(&env, ft_creat_env(env_join, var_env, content));
		(free(save), free(env_join));
	}
}

void	ft_export(t_var *var, char **cmd)
{
	int		i;
	char	*var_env;

	if (!cmd[1])
		displaye_env(var);
	else
	{
		while (*++cmd)
		{
			if (!check_str_exp(*cmd, var, &i))
				continue ;
			var_env = ft_substr(*cmd, 0, i);
			if (is_existe(var->env, var_env, *cmd, i))
				free(var_env);
			else
				add_var_to_list(var->env, var_env, *cmd, i);
			if (!ft_strcmp(var_env, "PATH"))
				var->flag = 0;
			var->status = 0;
		}
	}
}
