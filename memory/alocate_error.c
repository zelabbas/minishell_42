/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alocate_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:26:37 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:26:39 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	allocate_error(char *str)
{
	ft_putstr_fd("bash : malloc: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
