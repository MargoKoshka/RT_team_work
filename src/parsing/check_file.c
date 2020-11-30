/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:27:17 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:27:18 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		closing_commas(char *str)
{
	int i;

	i = 0;
	while (str[i] != 0)
	{
		if (((str[i] == '}') || (str[i] == ']')) && (str[i - 1] == ','))
			return (0);
		i++;
	}
	return (1);
}

int		brackets(char *str)
{
	int i;
	int counter1;
	int counter2;

	i = 0;
	counter1 = 0;
	counter2 = 0;
	while (str[i] != 0)
	{
		if (str[i] == '{')
			counter1++;
		if (str[i] == '}')
			counter1--;
		if (str[i] == '[')
			counter2++;
		if (str[i] == ']')
			counter2--;
		i++;
	}
	if ((counter1 != 0) || (counter2 != 0))
		return (0);
	return (1);
}

int		is_lettters_in_brackets(char *str)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i] != 0)
	{
		if (str[i] == ']')
		{
			if (str[i - 1] != '}')
				counter--;
		}
		else if (counter != 0 && (str[i] != '.' && str[i] != ',' \
			&& str[i] != '-' && str[i] != '+' && ft_isdigit(str[i]) != 1))
			return (0);
		else if (counter != 0 && str[i] == '.' && ft_isdigit(str[i - 1]) != 1)
			return (0);
		else if ((str[i] == '[') && (str[i + 1] != '{'))
			counter++;
		i++;
	}
	return (1);
}

void	check_file(char *str)
{
	if (closing_commas(str) == 0)
		file_contents_error();
	if (brackets(str) == 0)
		file_contents_error();
	if (is_lettters_in_brackets(str) == 0)
		file_contents_error();
}
