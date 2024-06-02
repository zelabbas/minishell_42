/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:19:37 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:19:39 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

// Determine the token type based on the beginning of the string.
t_token	check_tok(char *str)
{
	if (str[0] == '|' && str[1] == '|')
		return (OR);
	if (str[0] == '&' && str[1] == '&')
		return (AND);
	if (str[0] == '>' && str[1] == '>')
		return (REDIR_APPEND);
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	if (str[0] == '|')
		return (PIPE);
	if (str[0] == ')')
		return (BRKT_CLOSE);
	if (str[0] == '(')
		return (BRKT_OPEN);
	if (str[0] == '>')
		return (REDIR_OUT);
	if (str[0] == '<')
		return (REDIR_IN);
	return (EXPR);
}

// Check if the string contains a delimiter at the specified index.
int	ft_check_delim(char *str, int i)
{
	if (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (2);
		else if (str[i] == '&' && str[i + 1] == '&' && str[i + 2] == '&')
			return (-1);
		else if (str[i] == '&' && str[i + 1] == '&')
			return (2);
		else if (str[i] == '&')
			return (-1);
		else if (str[i] == '|')
			return (1);
		else if (str[i] == ')' || str[i] == '(')
			return (1);
		else
			return (0);
	}
	return (-1);
}

// Check if this character is a bracket.
int	ft_is_bracket(char c)
{
	return (c == ')' || c == '(');
}

// Check if the character is a whitespace character.
int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

// return the precedence depends on the token
int	ft_precedence(t_token token)
{
	if (token == REDIR_IN || token == REDIR_OUT
		|| token == REDIR_APPEND || token == HEREDOC)
		return (4);
	else if (token == PIPE)
		return (3);
	else if (token == AND || token == OR)
		return (2);
	else
		return (1);
}
