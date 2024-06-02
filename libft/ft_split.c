/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:27:47 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:27:48 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

static int	check_separator(char s, char charset)
{
	return (s == charset);
}

static int	count_strings(char const *str, char charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && check_separator(str[i], charset))
			i++;
		if (str[i])
			count++;
		while (str[i] && !check_separator(str[i], charset))
			i++;
	}
	return (count);
}

static char	*ft_word(const char **str, char charset)
{
	int			len_word;
	int			i;
	const char	*start;
	char		*word;

	len_word = 0;
	start = *str;
	while (**str && **str != charset)
	{
		len_word++;
		(*str)++;
	}
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	*str = start;
	i = 0;
	while (i < len_word)
	{
		word[i] = **str;
		(*str)++;
		i++;
	}
	word[len_word] = '\0';
	return (word);
}

static void	*ft_free_all_split_alloc(char **split, size_t elts)
{
	size_t	i;

	i = 0;
	while (i < elts)
	{
		free(split[i]);
		i++;
	}
	free(split);
	ft_putstr_fd("bash : malloc: ", 2);
	ft_putstr_fd("faild to allocate memory\n", 2);
	exit(1);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	char	**strings;

	if (!str)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (count_strings(str, c) + 1));
	if (!strings)
		allocate_error(strerror(errno));
	i = 0;
	while (*str)
	{
		while (*str && check_separator(*str, c))
			str++;
		if (*str)
		{
			strings[i] = ft_word(&str, c);
			if (!strings[i])
				return (ft_free_all_split_alloc(strings, i));
			i++;
		}
	}
	strings[i] = 0;
	return (strings);
}
