/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:32:37 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:34:25 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

char	*ft_get_envvar(t_var var, char *env_var)
{
	t_env	*env;

	env = var.env;
	while (env)
	{
		if (!ft_strcmp(env->var, env_var))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

int	ft_oldpwd(t_env *env, char *oldpwd)
{
	char	*env_var;
	char	*tmp;

	if (ft_env_search(env, "OLDPWD"))
		return (ft_env_replace(ft_env_search(env, "OLDPWD"), "OLDPWD", oldpwd));
	tmp = ft_strjoin("OLDPWD", "=");
	env_var = ft_strjoin(tmp, oldpwd);
	ft_add_env(&env, ft_creat_env(env_var, "OLDPWD", oldpwd));
	free(tmp);
	free(env_var);
	return (0);
}

void	ft_print_cd_error(char *pwd)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(pwd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	ft_update_env(t_var *var, char *pwd, char *oldpwd, char *tmp_pwd)
{
	if (chdir(pwd) != 0)
	{
		ft_print_cd_error(pwd);
		var->status = 1;
		free(pwd);
		return ;
	}
	if (!getcwd(tmp_pwd, PATH_MAX))
	{
		var->status = 0;
		ft_print_cd_error("error retrieving current directory: \
			getcwd: cannot access parent directories");
	}
	free(pwd);
	pwd = ft_strdup(tmp_pwd);
	if (ft_env_replace(ft_env_search(var->env, "PWD"), "PWD", pwd)
		|| ft_oldpwd(var->env, oldpwd))
		ft_putstr_fd("Error updating environment variables\n", 2);
	free(pwd);
	return ;
}

void	ft_cd(t_var *var, char **cmd)
{
	char	*pwd;
	char	oldpwd[PATH_MAX];
	char	tmp_pwd[PATH_MAX];

	if (!cmd[1])
	{
		pwd = ft_strdup(ft_get_envvar(*var, "HOME"));
		if (!pwd)
			return (var->status = 1,
				ft_putstr_fd("HOME environment variable is not set\n", 2));
	}
	else
		pwd = ft_strdup(cmd[1]);
	getcwd(oldpwd, PATH_MAX);
	ft_update_env(var, pwd, oldpwd, tmp_pwd);
}
