/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:28:25 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:28:27 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		parsing_type(char *str, int *index)
{
	int rez;
	int i;

	rez = 0;
	i = *index + 1;
	*index = *index + 1;
	if ((find_quotes(str, index, "\"sun\"\0")))
		return (rez = e_direct);
	*index = i;
	if ((find_quotes(str, index, "\"lamp\"\0")))
		return (rez = e_point);
	*index = i;
	if ((find_quotes(str, index, "\"ambient\"\0")))
		return (rez = e_ambient);
	return (rez);
}

void	intensity_parsing(char *str, int *index, t_rtv *rt, int n)
{
	*index = *index + 1;
	rt->lights[n]->intensity = rt_atof(&str[*index]);
	while ((str[*index] != '}') && (str[*index] != ','))
		*index = *index + 1;
	if (str[*index] == '}')
		*index = *index + 3;
	else if (str[*index] == ',')
		*index = *index + 1;
}
