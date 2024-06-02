/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:20:21 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:20:23 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

// Print a syntax error message.
int	ft_print_syntax_error(char *msg, char *c, int count)
{
	int	i;

	i = -1;
	if (!c)
	{
		ft_putstr_fd("bash: syntax error ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("bash: syntax error ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(" `", 2);
		while (++i < count)
			write(1, &c[i], 1);
		ft_putstr_fd("'\n", 2);
	}
	return (-1);
}

/* Trim leading and trailing spaces from the input string and
condense consecutive spaces to a single space. */
char	*ft_clean_input(char *str)
{
	char	*result;

	result = ft_strtrim(str, " \t");
	free(str);
	return (result);
}

// Check the validity of the starting token in the input string.
int	ft_first_check(char *str)
{
	t_token	tok;

	tok = check_tok(str);
	if (tok == PIPE || tok == OR
		|| tok == AND || tok == BRKT_CLOSE)
	{
		if (tok == PIPE || tok == BRKT_CLOSE)
			ft_print_syntax_error("near unexpected token", str, 1);
		else
			ft_print_syntax_error("near unexpected token", str, 2);
		free(str);
		return (0);
	}
	return (1);
}

// creation of the herdoc redirection linked list
void	ft_heredoc_syntax(t_redir *red, t_var *var)
{
	t_redir	*tmp_red;
	t_redir	*tmp_herdoc;

	tmp_red = red;
	while (tmp_red)
	{
		if (tmp_red->tok == HEREDOC)
		{
			if (var->error_herdoc == NULL)
				var->error_herdoc = ft_create_rednode(
						ft_strdup(tmp_red->file), HEREDOC);
			else
			{
				tmp_herdoc = var->error_herdoc;
				while (tmp_herdoc->rchild)
					tmp_herdoc = tmp_herdoc->rchild;
				tmp_herdoc->rchild = ft_create_rednode(
						ft_strdup(tmp_red->file), HEREDOC);
			}
		}
		tmp_red = tmp_red->rchild;
	}
}

// detecting syntax errors related to parentheses in the input command line.
int	check_parentheses_error(char *line, t_var *var, t_redir *red)
{
	int	i;

	i = 0;
	if (check_tok(&line[i]) == BRKT_OPEN)
	{
		ft_heredoc_syntax(red, var);
		ft_free_red(red);
		ft_print_syntax_error("near unexpected token", "(", 1);
		return (-1);
	}
	if (check_tok(&line[i]) == BRKT_CLOSE)
	{
		i++;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == ')' || line[i] == '('
			|| (ft_check_delim(line, i) <= 0 && line[i]))
		{
			ft_heredoc_syntax(red, var);
			ft_free_red(red);
			ft_print_syntax_error("near unexpected token", ")", 1);
			return (-1);
		}
	}
	return (0);
}
