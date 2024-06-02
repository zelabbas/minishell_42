/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_help_expd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:29:42 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:29:43 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	ft_init(t_exp *expand)
{
	expand->bf1 = NULL;
	expand->bf2 = NULL;
	expand->head = NULL;
	expand->open = 0;
	expand->i = 0;
	expand->flag = 0;
}

int	is_del(char c)
{
	if (ft_isalnum(c))
		return (0);
	return (1);
}

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13) || c == 127)
		return (1);
	return (0);
}

char	*ft_chartostr(char c)
{
	char	str[2];

	str[0] = c;
	str[1] = 0;
	return (ft_strdup(str));
}

int	check_etoile(char *str)
{
	int	i;

	if (!*str)
		return (1);
	i = -1;
	while (str[++i] && str[i] == '*')
		;
	if (!str[i])
		return (0);
	return (1);
}
