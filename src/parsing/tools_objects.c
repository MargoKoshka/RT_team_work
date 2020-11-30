/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:28:31 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:28:32 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		go_to_coma(char *str, int i)
{
	while (str[i] != ',')
		i++;
	i++;
	return (i);
}

int		parsing_texture2(char *str, int *index, int i, int rez)
{
	*index = i;
	if ((find_quotes(str, index, "\"CHESS\"\0")))
		return (rez = CHESS);
	*index = i;
	if ((find_quotes(str, index, "\"BRICS\"\0")))
		return (rez = BRICS);
	*index = i;
	if ((find_quotes(str, index, "\"BLUR\"\0")))
		return (rez = BLUR);
	*index = i;
	if ((find_quotes(str, index, "\"GRASS\"\0")))
		return (rez = GRASS);
	if ((find_quotes(str, index, "\"MARBLE\"\0")))
		return (rez = MARBLE);
	if ((find_quotes(str, index, "\"PERLIN\"\0")))
		return (rez = PERLIN);
	if ((find_quotes(str, index, "\"RAINBOW\"\0")))
		return (rez = RAINBOW);
	return (rez);
}

int		parsing_texture(char *str, int *index)
{
	int	rez;
	int	i;

	rez = 0;
	i = *index + 1;
	*index = *index + 1;
	if ((f(str, index, "\"NO_TEXTURE\"\0")))
		return (rez = NO_TEXTURE);
	*index = i;
	if ((f(str, index, "\"EARTH\"\0")))
		return (rez = EARTH);
	*index = i;
	if ((f(str, index, "\"CHESS\"\0")) || (f(str, index, "\"BRICS\"\0")) || \
	(f(str, index, "\"PERLIN\"\0")) || (f(str, index, "\"BLUR\"\0")) || \
	(f(str, index, "\"GRASS\"\0")) || (f(str, index, "\"MARBLE\"\0")) ||\
	(f(str, index, "\"RAINBOW\"\0")))
		return (rez = parsing_texture2(str, index, i, rez));
	*index = i;
	return (rez);
}

double	double_parsing(char *str, int *index)
{
	double res;

	res = 0;
	*index = *index + 1;
	res = rt_atof(&str[*index]);
	while (((str[*index] >= '0') && (str[*index] <= '9')) || \
	(str[*index] == '.') || (str[*index] == '+') || (str[*index] == '-'))
		*index = *index + 1;
	if ((ft_strlen(str) - *index) < 5)
		return (res);
	while (str[*index] != ',')
		*index = *index + 1;
	*index = *index + 1;
	return (res);
}

int		int_parsing(char *str, int *index)
{
	int res;

	res = 0;
	*index = *index + 1;
	res = ft_atoi(&str[*index]);
	while (((str[*index] >= '0') && (str[*index] <= '9')) || \
	(str[*index] == '+') || (str[*index] == '-'))
		*index = *index + 1;
	if ((ft_strlen(str) - *index) < 5)
		return (res);
	while (str[*index] != ',')
		*index = *index + 1;
	*index = *index + 1;
	return (res);
}
