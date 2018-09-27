/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q5.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 23:40:57 by cababou           #+#    #+#             */
/*   Updated: 2018/09/16 22:17:22 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "drawline.h"

static inline void	wrt_pxl(t_image *img, int x, int y, int color)
{
	if (x > 0 && x < img->width && y > 0 && y < img->height)
		img->image[x + img->width * y] = color;
}

void				l1(t_line *l)
{
	while ((l->x = l->x + 1) != l->p2->x)
	{
		wrt_pxl(l->img, l->x, l->y,
		calc_gradient(l->p1->color, l->p2->color,
		((double)(l->x - l->p1->x)) / ((double)(l->p2->x - l->p1->x))));
	}
}

void				l2(t_line *l)
{
	while ((l->x = l->x - 1) != l->p2->x)
	{
		wrt_pxl(l->img, l->x, l->y,
		calc_gradient(l->p1->color, l->p2->color,
		((double)(l->x - l->p1->x)) / ((double)(l->p2->x - l->p1->x))));
	}
}

void				l3(t_line *l)
{
	while ((l->y = l->y + 1) != l->p2->y)
	{
		wrt_pxl(l->img, l->x, l->y,
		calc_gradient(l->p1->color, l->p2->color,
		((double)(l->y - l->p1->y)) / ((double)(l->p2->y - l->p1->y))));
	}
}

void				l4(t_line *l)
{
	while ((l->y = l->y - 1) != l->p2->y)
	{
		wrt_pxl(l->img, l->x, l->y,
		calc_gradient(l->p1->color, l->p2->color,
		((double)(l->y - l->p1->y)) / ((double)(l->p2->y - l->p1->y))));
	}
}
