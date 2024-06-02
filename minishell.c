/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:32:56 by skarim            #+#    #+#             */
/*   Updated: 2024/06/02 22:25:38 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "included/minishell.h"

int	g_signel = 0;

void	ft_handle_error_herdoc(t_var *g_var)
{
	t_redir	*tmp;

	if (g_var->error_herdoc)
	{
		tmp = g_var->error_herdoc;
		while (tmp)
		{
			error_heredoc(tmp, g_var);
			tmp = tmp->rchild;
		}
	}
	g_signel = 0;
	ft_free_red(g_var->error_herdoc);
	g_var->error_herdoc = NULL;
}

void	start_handle(char *input, t_node *root, t_var *g_var)
{
	g_signel = 1;
	if (input[0])
		add_history(input);
	root = parsing(input, g_var);
	if (!root)
		return (ft_handle_error_herdoc(g_var));
	ft_free_red(g_var->error_herdoc);
	g_var->error_herdoc = NULL;
	handle_herdoc(root, g_var);
	execution(root, g_var);
	g_signel = 0;
	return_in_out_fd(g_var);
	free_tree(root);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_var	g_var;
	t_node	*root;

	((void)ac, (void)av);
	initialization(&g_var, env);
	root = NULL;
	while (1 && isatty(STDIN_FILENO))
	{
		ft_signal();
		input = readline("->Prompt: ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		start_handle(input, root, &g_var);
	}
	free_all(&g_var);
	return (0);
}