/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:28:42 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:28:44 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			count_spaces(char *str)
{
	int n;
	int i;

	n = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			n++;
		i++;
	}
	return (n);
}

t_vector	parsing_coordinates(char *str, int *index)
{
	int			i;
	t_vector	rez;

	i = 0;
	i = *index + 2;
	rez.x = rt_atof(&str[i]);
	while (str[i] != ',')
		i++;
	i++;
	rez.y = rt_atof(&str[i]);
	while (str[i] != ',')
		i++;
	i++;
	rez.z = rt_atof(&str[i]);
	while (str[i] != ',')
		i++;
	*index = i;
	return (rez);
}

t_vector	parsing_angles(char *str, int *index)
{
	int			i;
	double		pi_radian;
	t_vector	result;

	pi_radian = PI / 180;
	i = 0;
	i = *index + 2;
	result.x = rt_atof(&str[i]) * pi_radian;
	while (str[i] != ',')
		i++;
	i++;
	result.y = rt_atof(&str[i]) * pi_radian;
	while (str[i] != ',')
		i++;
	i++;
	result.z = rt_atof(&str[i]) * pi_radian;
	while (str[i] != ',')
		i++;
	i++;
	*index = i;
	return (result);
}
