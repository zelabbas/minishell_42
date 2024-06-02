/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:19:26 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:19:29 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

/* Return the index of the closing bracket ')' in the string,
starting from the given index 'i'. */
int	ft_find_bclose(char *line, int i)
{
	while (*line)
	{
		if (*line == ')')
			return (i);
		i++;
		line++;
	}
	return (-2);
}

/* Skips characters in the input string until the end of a quoted section.*/
int	ft_skip_for_quotes(char *line, int *i)
{
	char	c;

	if (line[*i] == '\"' || line[*i] == '\'')
	{
		c = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != c)
			(*i)++;
		if (!line[*i])
			return (-1);
		return (0);
	}
	return (ft_check_delim(line, *i));
}

/* Check if the character after a delimiter
in the input line introduces a syntax error.*/
int	ft_handle_delimiters(char *line, int *index)
{
	if ((ft_check_delim(line, *index) && check_tok(line + *index)
			!= BRKT_OPEN) || !line[*index])
	{
		if (!line[*index])
			return (ft_print_syntax_error("near unexpected token `newline'",
					NULL, -1));
		return (ft_print_syntax_error("near unexpected token",
				&line[*index], 1), -1);
	}
	return (0);
}

// Check the syntax combination and validate the string after a delimiter.
int	ft_check_syntax_combination(char *line, int *index,
	int *bclose, t_token tok)
{
	*index += ft_check_delim(line, *index);
	if (tok == BRKT_OPEN)
	{
		if (!*bclose)
			*bclose = *index;
		*bclose = ft_find_bclose(line + *bclose, *bclose) + 1;
		if (*bclose == -1)
			return (ft_print_syntax_error("unclosed parentheses", NULL, -1));
	}
	else if (tok == BRKT_CLOSE)
		if (*index > *bclose)
			return (ft_print_syntax_error("near unexpected token", ")", 1));
	while (ft_isspace(line[*index]))
		(*index)++;
	if (tok == BRKT_CLOSE)
		return (0);
	return (ft_handle_delimiters(line, index));
}

/* Check and find the length of a word (file name or command)
 when it is enclosed in double or single quotes.*/
int	ft_protected_word(char *line, int *i, int *len, char c)
{
	(*i)++;
	(*len)++;
	while (line[*i])
	{
		if (line[*i] == c)
			return (1);
		(*i)++;
		(*len)++;
	}
	return (-1);
}
