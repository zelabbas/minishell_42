/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:11 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:28:12 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	return_in_out_fd(t_var *var)
{
	dup2(var->fd_input, STDIN_FILENO);
	dup2(var->fd_output, STDOUT_FILENO);
}

void	init_g_var(t_var *var)
{
	var->env = NULL;
	var->status = 0;
	var->fd_input = dup(STDIN_FILENO);
	var->fd_output = dup(STDOUT_FILENO);
	var->flag = 0;
	var->error_herdoc = NULL;
}

int	find_char(char *env, char c)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (env[i] == c)
			return (i);
	}
	return (-1);
}

void	ft_main_env(t_var *var)
{
	char	*cwd;
	char	*tmp;
	char	*path;

	path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", cwd);
	ft_add_env(&var->env, ft_creat_env(tmp, ft_strdup("PWD"), cwd));
	free(tmp);
	tmp = ft_strjoin("PATH=", path);
	ft_add_env(&var->env, ft_creat_env(tmp, ft_strdup("PATH"), path));
	free(tmp);
	tmp = ft_strjoin("SHLVL=", "1");
	ft_add_env(&var->env, ft_creat_env(tmp, ft_strdup("SHLVL"),
			ft_strdup("1")));
	free(tmp);
	tmp = ft_strjoin("_=", "/usr/bin/env");
	ft_add_env(&var->env, ft_creat_env(tmp, ft_strdup("_"),
			ft_strdup("/usr/bin/env")));
	free(tmp);
	tmp = ft_strdup("OLDPWD");
	ft_add_env(&var->env, ft_creat_env(tmp, ft_strdup(tmp),
			ft_strdup("")));
	free(tmp);
	var->flag = 1;
}

void	initialization(t_var *var, char **env)
{
	int		i;
	char	*tmp;

	init_g_var(var);
	if (!env || !(*env))
	{
		ft_putstr_fd("TERM environment variable not set.!\n", 2);
		ft_main_env(var);
		return ;
	}
	while (*env)
	{
		i = find_char(*env, '=');
		ft_add_env(&var->env, ft_creat_env(*env, ft_substr(*env, 0, i),
				ft_strdup(*env + i + 1)));
		env++;
	}
	tmp = ft_search_var("OLDPWD", var);
	if (!tmp)
	{
		ft_add_env(&var->env, ft_creat_env("OLDPWD",
				ft_strdup("OLDPWD"), ft_strdup("")));
	}
	else
		free(tmp);
}
