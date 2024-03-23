/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:05:49 by hlahrach          #+#    #+#             */
/*   Updated: 2021/11/11 21:56:52 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_check_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\n')
		i++;
	return (i);
}

int	check_max(unsigned long long res, int signe)
{
	if (res >= 9223372036854775807)
	{
		if (signe > 0)
			return (-1);
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	res;

	i = ft_check_spaces (str);
	signe = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (check_max(res, signe) <= 0)
			return (check_max(res, signe));
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * signe);
}
