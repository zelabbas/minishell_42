/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:14 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 17:31:23 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

// this function creat a new node that will represent env 
t_env	*ft_creat_env(char *env, char *var, char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		allocate_error(strerror(errno));
	node->env = ft_strdup(env);
	node->var = var;
	if (!ft_strcmp(var, "SHLVL"))
	{
		if (ft_atoi(content) != 999)
			node->content = ft_itoa(ft_atoi(content) + 1);
		else
			node->content = ft_strdup("");
		free(node->env);
		node->env = ft_strjoin("SHLVL=", node->content);
		free(content);
	}
	else
		node->content = content;
	node->next = NULL;
	return (node);
}

t_env	*ft_creat_env_exp(char *env, char *var, char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		allocate_error(strerror(errno));
	node->env = ft_strdup(env);
	node->var = var;
	node->content = content;
	node->next = NULL;
	return (node);
}

// this function add the new node in the last of list 
void	ft_add_env(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!head)
		return ;
	if (!(*head))
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/* Searches for an environment variable by its 
key and returns a pointer to its node.*/
t_env	*ft_env_search(t_env *env, char *key)
{
	while (env)
	{
		if (!strcmp(env->var, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

// Replaces the value of an environment variable with a new value.
int	ft_env_replace(t_env *env, char *key, char *value)
{
	char	*new_env;
	char	*tmp;

	if (!env)
		return (-1);
	tmp = ft_strjoin(key, "=");
	new_env = ft_strjoin(tmp, value);
	free(tmp);
	free(env->content);
	free(env->env);
	env->env = new_env;
	env->content = ft_strdup(value);
	return (0);
}
