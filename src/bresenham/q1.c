/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 22:33:16 by cababou           #+#    #+#             */
/*   Updated: 2018/09/16 22:17:10 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "drawline.h"
#include <stdio.h>

static inline void	wrt_pxl(t_image *img, int x, int y, int color)
{
	if (x > 0 && x < img->width && y > 0 && y < img->height)
		img->image[x + img->width * y] = color;
}

void				o1(t_line *l)
{
	l->e = l->dx;
	l->dx = l->e + l->e;
	l->dy = l->dy + l->dy;
	while (1)
	{
		wrt_pxl(l->img, l->x, l->y,
		calc_gradient(l->p1->color, l->p2->color,
		((double)(l->x - l->p1->x)) / ((double)(l->p2->x - l->p1->x))));
		if ((l->x = l->x + 1) == l->p2->x)
			break ;
		if ((l->e = l->e - l->dy) <= 0)
		{
			l->y = l->y + 1;
			l->e = l->e + l->dx;
		}
	}
}

void				o2(t_line *l)
{
	l->e = l->dy;
	l->dy = l->e + l->e;
	l->dx = l->dx + l->dx;
	while (1)
	{
		wrt_pxl(l->img, l->x, l->y,
		calc_gradient(l->p1->color, l->p2->color,
		((double)(l->y - l->p1->y)) / ((double)(l->p2->y - l->p1->y))));
		if ((l->y = l->y + 1) == l->p2->y)
			break ;
		if ((l->e = l->e - l->dx) <= 0)
		{
			l->x = l->x + 1;
			l->e = l->e + l->dy;
		}
	}
}

void				q1(t_line *l)
{
	if (l->dx >= l->dy)
	{
		o1(l);
	}
	else
	{
		o2(l);
	}
}
