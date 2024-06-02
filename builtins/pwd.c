/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:05 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:28:06 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

void	ft_pwd(t_var *var)
{
	char	s[PATH_MAX];

	getcwd(s, PATH_MAX);
	printf("%s\n", s);
	var->status = 0;
}
