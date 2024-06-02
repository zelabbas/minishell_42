/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:29:39 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:29:40 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

int	size_list_exp(t_list *head)
{
	int		size;
	t_list	*tmp;

	size = 0;
	tmp = head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**ft_list_to_2d(t_list *head)
{
	t_list	*tmp;
	char	**tab;
	int		size;
	int		i;

	if (!head)
		return (NULL);
	size = size_list_exp(head);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		allocate_error(strerror(errno));
	i = 0;
	tmp = head;
	while (tmp)
	{
		tab[i] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_search_var(char *key, t_var *var)
{
	t_env	*tmp;

	tmp = var->env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->var))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_list_cwd(t_list **head)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
			ft_lstadd_back(head, ft_lstnew(ft_strdup(entry->d_name)));
		entry = readdir(dir);
	}
	closedir(dir);
	return ;
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ptr = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!ptr)
		allocate_error(strerror(errno));
	while (s1[i])
		(1) && (ptr[i] = s1[i], i++);
	while (s2[j])
		(1) && (ptr[i] = s2[j], i++, j++);
	ptr[i] = '\0';
	(free(s1), free(s2));
	return (ptr);
}
