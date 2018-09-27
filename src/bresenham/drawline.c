/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 12:17:02 by cababou           #+#    #+#             */
/*   Updated: 2018/09/16 22:35:23 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "drawline.h"

void		extension_1(t_line *l)
{
	if (l->dx > 0)
	{
		if ((l->dy = l->p2->y - l->p1->y))
		{
			if (l->dy > 0)
				q1(l);
			else
				q2(l);
		}
		else
			l1(l);
	}
	else
	{
		if ((l->dy = l->p2->y - l->y) != 0)
		{
			if (l->dy > 0)
				q3(l);
			else
				q4(l);
		}
		else
			l2(l);
	}
}

void		init_line(t_params *p, t_point *p1, t_point *p2)
{
	t_line *l;

	l = p->fdf_window->line;
	l->p1 = p1;
	l->p2 = p2;
	l->e = l->p2->x - l->p1->x;
	l->dx = l->e * 2;
	l->dy = (l->p2->y - l->p1->y) * 2;
	l->x = l->p1->x;
	l->y = l->p1->y;
}

void		line(t_params *p, t_image *img)
{
	t_line	*l;

	l = p->fdf_window->line;
	l->img = img;
	write_pxl(l->img, l->p1->x, l->p1->y,
		calc_gradient(l->p1->color, l->p2->color, 0.0));
	write_pxl(l->img, l->p2->x, l->p2->y,
		calc_gradient(l->p1->color, l->p2->color, 1.0));
	if ((l->dx = l->p2->x - l->p1->x) != 0)
	{
		extension_1(l);
	}
	else if (l->dx == 0)
	{
		if ((l->dy = l->p2->y - l->y) != 0)
		{
			if (l->dy > 0)
				l3(l);
			else if (l->dy < 0)
				l4(l);
		}
	}
}
