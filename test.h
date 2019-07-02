/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_op.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:08:48 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/02 15:39:50 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdint.h>
# define MEM_SIZE	4096
# define PC(x)		(((x) - 1) % MEM_SIZE)

// typedef struct					s_cod
// {
// 	unsigned					arg4 : 2;
// 	unsigned					arg3 : 2;
// 	unsigned					arg2 : 2;
// 	unsigned					arg1 : 2;
// }								t_cod;

typedef struct					s_cws
{
	uint32_t					cycles;
	uint32_t					num_check;
	uint32_t					cycles_check;
	uint32_t					cycles_to_die;
	union
	{
		uint8_t					b;
		struct
		{	
			unsigned			v1 : 1;
			unsigned			v2 : 1;
			unsigned			v3 : 1;
			unsigned			v4 : 1;
		}						f;
	}							flg;
}								t_cws;

#endif
