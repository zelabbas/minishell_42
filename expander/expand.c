/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:39 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 16:51:30 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	ft_add(t_exp *exp, t_var *var)
{
	if (exp->bf1)
	{
		if (!check_etoile(exp->bf1) && !exp->flag)
		{
			ft_list_cwd(&exp->head);
			free(exp->bf1);
		}
		else
		{
			if (!ft_strcmp("~", exp->bf1))
			{
				free(exp->bf1);
				exp->bf1 = ft_search_var("HOME", var);
			}
			ft_lstadd_back(&exp->head, ft_lstnew(exp->bf1));
		}
		exp->bf1 = NULL;
		exp->flag = 0;
	}
}

void	ft_join_char(t_exp *exp, char *prompt)
{
	if (exp->open == 0)
	{
		exp->open = prompt[exp->i];
		exp->flag = 1;
	}
	else if (exp->open == prompt[exp->i])
	{
		if (!exp->bf1 && (prompt[exp->i + 1] == ' ' || !prompt[exp->i + 1]))
			exp->bf1 = ft_strdup("");
		exp->open = 0;
		if (!exp->bf1 || (prompt[exp->i] == prompt[exp->i - 1]
				&& !check_etoile(exp->bf1)))
			exp->flag = 0;
	}
	else
		exp->bf1 = ft_strjoin_2(exp->bf1, ft_chartostr(prompt[exp->i]));
}

void	ft_help_dollr(char *s, t_exp *exp, t_var *var)
{
	if (!ft_strcmp(exp->bf2, "$") && s[exp->i] != '?')
		exp->bf1 = ft_strjoin_2(exp->bf1, exp->bf2);
	else
	{
		exp->bf1 = ft_strjoin_2(exp->bf1, ft_search_var(exp->bf2 + 1, var));
		free(exp->bf2);
	}
	if (s[exp->i] == '?')
	{
		if (s[exp->i -1] == '$')
			exp->bf1 = ft_strjoin_2(exp->bf1, ft_itoa(var->status));
		else
			exp->bf1 = ft_strjoin_2(exp->bf1, ft_chartostr(s[exp->i]));
	}
	else if (s[exp->i] && is_del(s[exp->i]) && s[exp->i] != '$'
		&& (s[exp->i + 1] != '\0' && s[exp->i + 1] != ' '))
		exp->bf1 = ft_strjoin_2(exp->bf1, ft_chartostr(s[exp->i]));
	exp->bf2 = NULL;
}

void	ft_expand_var_dollr(t_exp *exp, char *s, t_var *var)
{
	while (s[exp->i] && s[exp->i] == '$')
	{
		exp->bf2 = ft_chartostr(s[exp->i]);
		exp->i++;
		while (s[exp->i] && !is_del(s[exp->i]))
		{
			exp->bf2 = ft_strjoin_2(exp->bf2, ft_chartostr(s[exp->i]));
			if (ft_isdigit(exp->bf2[1]))
				break ;
			exp->i++;
		}
		ft_help_dollr(s, exp, var);
	}
}

char	**ft_expand(char *prompt, t_var *var)
{
	t_exp	exp;
	char	**tab;

	ft_init(&exp);
	tab = NULL;
	while (prompt[exp.i])
	{
		if ((is_white_space(prompt[exp.i])) && exp.open == 0)
			ft_add(&exp, var);
		else if (prompt[exp.i] == '"' || prompt[exp.i] == '\'')
			ft_join_char(&exp, prompt);
		else if (prompt[exp.i] == '$' && exp.open != '\'')
			ft_expand_var_dollr(&exp, prompt, var);
		else
			exp.bf1 = ft_strjoin_2(exp.bf1, ft_chartostr(prompt[exp.i]));
		if (!prompt[exp.i])
			break ;
		exp.i++;
	}
	ft_add(&exp, var);
	tab = ft_list_to_2d(exp.head);
	free_list(&exp.head);
	return (tab);
}
