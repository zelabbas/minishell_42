/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:29:04 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:29:09 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

int	update_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (128 + WTERMSIG(status) == 130)
			ft_putstr_fd("\n", 2);
		else if (128 + WTERMSIG(status) == 131)
			ft_putstr_fd("Quit: 3\n", 2);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	sigint_handler(int sig)
{
	(void) sig;
	if (!g_signel)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_midl_exec(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR
		|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		ft_putstr_fd("signal error in midlle\n", 2);
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	if (signal(SIGINT, sigint_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("signal error\n", 2);
}
