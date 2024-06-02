/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:27:16 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 00:27:18 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

// Indicate overflow by returning the -1
long long	ft_atoll(const char *str, int *i)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
				&& (*str - '0') > LLONG_MAX % 10))
			return (*i = -1);
		result = result * 10 + (*str++ - '0');
	}
	return (result * sign);
}
