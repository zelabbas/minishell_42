/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:28:32 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:28:33 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

char	*expand_file(char *file)
{
	int		open;
	char	*buffer;
	int		i;

	open = 0;
	buffer = NULL;
	i = -1;
	while (file[++i])
	{
		if (file[i] == '"' || file[i] == '\'')
		{
			if (open == 0)
				open = file[i];
			else if (open == file[i])
				open = 0;
			else
				buffer = ft_strjoin_2(buffer, ft_chartostr(file[i]));
		}
		else
			buffer = ft_strjoin_2(buffer, ft_chartostr(file[i]));
	}
	return (free(file), buffer);
}
