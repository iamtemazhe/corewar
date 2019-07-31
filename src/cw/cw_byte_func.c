/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_byte_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 14:58:12 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 14:10:13 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int32_t		cw_code_to_byte(const union u_map *src, int32_t pos, size_t n)
{
	int32_t	dst;

	dst = 0;
	while (n-- > 0)
		dst += src[PC(pos - n)].v.code << (n * 8);
	// if (n == 2)
		// ft_printf("dst = %x, dst_16 = %x\n\r", dst, (int16_t)dst);
	return (dst = (n < REG_SIZE) ? (int16_t)dst : dst);
}

void		cw_byte_to_code(union u_map *dst, int32_t pos, const void *src,\
																	size_t n)
{
	size_t	i;

	i = 0;
	while (n-- > 0)
	{
		dst[PCV(pos + i)].v.code = ((uint8_t *)src)[n];
		i++;
	}
}
