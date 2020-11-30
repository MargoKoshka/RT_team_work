/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:47 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:30:48 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				ft_free_wordtab(char **tab)
{
	int		i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i += 1;
	}
	free(tab);
	return (0);
}

size_t			ft_len_wordtab(char **tab)
{
	size_t len;

	len = 0;
	while (tab[len] != NULL)
		len += 1;
	return (len);
}

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
