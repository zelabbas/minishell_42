/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:27:42 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:27:43 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

// this function check if there's the flag -n or no
bool	option(char *str)
{
	if (!*str)
		return (false);
	if (*str == '-' && *(str + 1) != '\0')
	{
		str++;
		while (*str && *str == 'n')
			str++;
	}
	if (*str)
		return (false);
	return (true);
}

// this function display the full line reprsenting by tab 2d
void	ft_echo(char **cmd, t_var *var)
{
	int	opt;
	int	i;

	i = 0;
	opt = 0;
	while (cmd[++i] && option(cmd[i]))
		opt = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i])
			ft_putstr_fd(" ", 1);
	}
	if (!opt)
		ft_putstr_fd("\n", 1);
	var->status = 0;
}
