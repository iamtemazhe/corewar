/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_op.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:08:48 by jwinthei          #+#    #+#             */
/*   Updated: 2019/06/12 19:43:45 by hgysella         ###   ########.fr       */
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

typedef union					s_cod
{
	uint8_t						age;
	struct
	{	
		unsigned				rg4 : 2;
		unsigned				rg3 : 2;
		unsigned				rg2 : 2;
		unsigned				rg1 : 2;
	}							a;
}								t_cod;


typedef struct					s_cws
{
	uint32_t					cycles;
	uint32_t					num_check;
	uint32_t					cycles_check;
	uint32_t					cycles_to_die;
	union
	{
		uint8_t					age;
		struct
		{	
			unsigned			v4 : 2;
			unsigned			v3 : 2;
			unsigned			v2 : 2;
			unsigned			v1 : 2;
		}						arg;
	}							cod;
}								t_cws;

#endif
