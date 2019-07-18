/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:15:45 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/18 15:16:49 by jwinthei         ###   ########.fr       */
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
	*st_p = (st_st->n > 1) ? st_st->next : NULL;
	free(st_st);
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

t_stack			*st_new(size_t arg, size_t n)
{
	t_stack		*st_elem;

	if (!(st_elem = (t_stack*)malloc(sizeof(t_stack))))
		return (NULL);
	st_elem->next = st_elem;
	st_elem->n = n;
	st_elem->pc = arg;
	st_elem->cycle_to_show = CYCLE_TO_SHOW;
	st_elem->prev = st_elem;
	return (st_elem);
}

t_stack			*st_add(size_t arg, t_stack *st_dst)
{
	t_stack		*st_elem;

	if (!st_dst)
		return (st_dst = st_new(arg, 1));
	if (!(st_elem = st_new(arg, st_dst->n + 1)))
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