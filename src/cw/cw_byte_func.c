/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_byte_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 14:58:12 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 14:14:07 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int32_t		cw_code_to_byte(const union u_map *src, int32_t pos, uint8_t n)
{
	int32_t	dst;
	uint8_t	size;

	dst = 0;
	size = n;
	while (size-- > 0)
		dst += src[PC(pos - size)].v.code << (size * 8);
	return (dst = (n == IND_SIZE) ? (int16_t)dst : dst);
}

void		cw_byte_to_code(union u_map *dst, int32_t pos, const void *src,\
																	uint8_t n)
{
	uint8_t	i;

	i = 0;
	while (n-- > 0)
	{
		dst[PCV(pos + i)].v.code = ((uint8_t *)src)[n];
		i++;
	}
}
