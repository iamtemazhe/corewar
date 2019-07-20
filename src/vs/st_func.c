/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:15:45 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/20 13:41:22 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "stack.h"

void			st_del(t_stack **st_p)
{
	t_stack		*st_st;

	if (!(st_p && *st_p))
		return ;
	st_st = *st_p;
	st_st->prev->next = st_st->next;
	st_st->next->prev = st_st->prev;
	//*st_p = (st_st->n > 1) ? st_st->next : NULL;
	//free(st_st);
	st_st = NULL;
}

int8_t			st_err(int8_t retv, t_stack **st_p)
{
	t_stack		*st_tmp;

	if (!(st_p && *st_p))
		return (retv);
	while (1)
	{
		if (st_p[0]->n == 1)
		{
			st_del(st_p);
			break ;
		}
		st_tmp = st_p[0]->next;
		st_del(st_p);
		*st_p = st_tmp;
	}
	*st_p = NULL;
	return (retv);
}

t_stack			*st_new(t_cw *cw, size_t i_car, size_t n)
{
	t_stack		*st_elem;

	if (!(st_elem = (t_stack*)malloc(sizeof(t_stack))))
		return (NULL);
	st_elem->next = st_elem;
	st_elem->n = n;
	st_elem->pc = cw->pos;
	st_elem->id = -cw->car[i_car]->reg[0];
	st_elem->cycle_to_show = cw->cycles;
	st_elem->size = (IN(cw->car[i_car]->op_code) == LIVE) ? OP_SIZE : REG_SIZE;
	st_elem->prev = st_elem;
	return (st_elem);
}

t_stack			*st_add(t_cw *cw, size_t i_car, t_stack *st_dst)
{
	t_stack		*st_elem;

	if (!st_dst)
		return (st_dst = st_new(cw, i_car, 1));
	if (!(st_elem = st_new(cw, i_car, st_dst->n + 1)))
		return (NULL);
	if (st_dst->n == 1)
	{
		st_dst->next = st_elem;
		st_elem->prev = st_dst;
	}
	else
	{
		st_dst->prev->next = st_elem;
		st_elem->prev = st_dst->prev;
	}
	st_dst->prev = st_elem;
	st_elem->next = st_dst;
	st_dst = st_elem;
	return (st_dst);
}