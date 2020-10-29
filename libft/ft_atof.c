/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:30:07 by wrhett            #+#    #+#             */
/*   Updated: 2020/09/07 11:25:15 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_power(size_t nb, int power)
{
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	return (nb * ft_power(nb, power - 1));
}

double			ft_atof(const char *str)
{
	double	result;
	char	*mantisa;

	result = (double)ft_atoi(str);
	mantisa = ft_strchr(str, '.');
	if (mantisa != NULL)
	{
		mantisa += 1;
		if (result >= 0 && str[0] != '-')
			result += \
			(double)ft_atoi(mantisa) / ft_power(10, ft_strlen(mantisa));
		else
			result -= \
			(double)ft_atoi(mantisa) / ft_power(10, ft_strlen(mantisa));
	}
	return (result);
}
