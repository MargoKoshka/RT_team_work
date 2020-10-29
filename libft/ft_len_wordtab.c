/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_wordtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:34:20 by wrhett            #+#    #+#             */
/*   Updated: 2020/06/24 13:46:06 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_len_wordtab(char **tab)
{
	size_t len;

	len = 0;
	while (tab[len] != NULL)
		len += 1;
	return (len);
}
