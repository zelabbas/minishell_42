/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:35 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:28:36 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	ft_check_expand(char *s, bool *flag)
{
	if (find_char(s, '"') != -1 || find_char(s, '\'') != -1)
		*flag = false;
	else
		*flag = true;
}

void	init_var_exp_her(t_exp_herdoc *exp_her)
{
	exp_her->i = 0;
	exp_her->bf1 = NULL;
	exp_her->bf2 = NULL;
}

void	stor_var(char *str, t_exp_herdoc *ex_her)
{
	while (str[ex_her->i] && !is_del(str[ex_her->i]))
	{
		ex_her->bf2 = ft_strjoin_2(ex_her->bf2,
				ft_chartostr(str[ex_her->i]));
		ex_her->i++;
	}
}

void	handle_expande_herdoc(char *str, t_var *var, t_exp_herdoc *ex_her)
{
	if (str[ex_her->i] == '$')
	{
		ex_her->bf2 = ft_chartostr(str[ex_her->i]);
		ex_her->i++;
		stor_var(str, ex_her);
		if (str[ex_her->i] == '?' && (str[ex_her->i + 1] == ' '
				|| !str[ex_her->i + 1]))
		{
			ex_her->bf1 = ft_strjoin_2(ex_her->bf1, ft_itoa(var->status));
			free(ex_her->bf2);
		}
		else
		{
			ex_her->bf1 = ft_strjoin_2(ex_her->bf1,
					ft_search_var(ex_her->bf2 + 1, var));
			free(ex_her->bf2);
		}
		if (str[ex_her->i] != '?')
			ex_her->bf1 = ft_strjoin_2(ex_her->bf1,
					ft_chartostr(str[ex_her->i]));
	}
	else
		ex_her->bf1 = ft_strjoin_2(ex_her->bf1, ft_chartostr(str[ex_her->i]));
}

char	*expand_herdoc(char *str, t_var *var)
{
	t_exp_herdoc	exp_her;

	init_var_exp_her(&exp_her);
	while (str[exp_her.i])
	{
		handle_expande_herdoc(str, var, &exp_her);
		if (!str[exp_her.i])
			break ;
		exp_her.i++;
	}
	return (free(str), exp_her.bf1);
}
