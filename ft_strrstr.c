/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:21:12 by hgysella          #+#    #+#             */
/*   Updated: 2019/06/06 15:25:29 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strrstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;

	i = ft_strlen(haystack) - 1;
	j = ft_strlen(needle) - 1;
	while (j >= 0)
	{
		if (haystack[i] != needle[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}