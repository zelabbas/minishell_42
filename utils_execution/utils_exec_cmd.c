/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:29:26 by zelabbas          #+#    #+#             */
/*   Updated: 2024/05/28 17:03:54 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

int	check_slach(char *s, t_var *var)
{
	if (find_char(s, '/') == -1)
	{
		error_cmd_not_found(s);
		var->status = 127;
		return (1);
	}
	return (0);
}

int	ft_size_list(t_env *env)
{
	t_env	*tmp;
	int		size;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**get_paths(t_var *var)
{
	t_env	*tmp;

	tmp = var->env;
	while (tmp)
	{
		if (!ft_strcmp("PATH", tmp->var))
			return (ft_split(tmp->content, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_var *var)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	paths = get_paths(var);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		if (access(path,F_OK) == 0)
			return (free_matrix(paths), free(part_path), path);
		free(path);
		free(part_path);
	}
	return (free_matrix(paths), NULL);
}

char	**env_list_to_tab(t_env *env)
{
	int		size;
	int		i;
	t_env	*tmp;
	char	**tab;

	size = ft_size_list(env);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env)
		allocate_error("faild to allocate memory");
	i = 0;
	tmp = env;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->env);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
