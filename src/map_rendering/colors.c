/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 02:19:42 by cababou           #+#    #+#             */
/*   Updated: 2018/09/16 23:29:25 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>

void	calculate_max_colors(t_params *p, t_tab *tab)
{
	t_list	*element;
	t_point	*point;

	element = tab->point_list->firstelement;
	tab->min_z = new_fpt(p, 0, 0, 0);
	tab->max_z = new_fpt(p, 0, 0, 0);
	while (element)
	{
		point = (t_point *)element->content;
		if (element->prev == NULL)
			set_point(tab->min_z, point->x, point->y, point->z);
		if (element->prev == NULL)
			set_point(tab->max_z, point->x, point->y, point->z);
		if (point->z > tab->max_z->z)
		{
			set_point(tab->max_z, point->x, point->y, point->z);
			tab->max_z->color = point->color < 0 ? MAX_COLOR : point->color;
		}
		if (point->z < tab->min_z->z)
		{
			set_point(tab->min_z, point->x, point->y, point->z);
			tab->min_z->color = point->color < 0 ? MIN_COLOR : point->color;
		}
		element = element->next;
	}
}

void	calculate_all_colors(t_params *p, t_tab *tab)
{
	t_list	*element;
	t_point	*point;
	double	stage;

	(void)p;
	element = tab->point_list->firstelement;
	stage = 0.0;
	while (element)
	{
		point = (t_point *)element->content;
		if (point->color < 0)
		{
			if ((tab->max_z->z - tab->min_z->z) == 0)
				stage = 0;
			else
				stage = ((double)(point->z - tab->min_z->z))
					/ (tab->max_z->z - tab->min_z->z);
			point->color = calc_gradient(MIN_COLOR, MAX_COLOR, stage);
		}
		element = element->next;
	}
}

void	randomize_all_colors(t_params *p, t_tab *tab)
{
	t_list	*element;
	t_point	*point;

	(void)p;
	element = tab->point_list->firstelement;
	while (element)
	{
		point = (t_point *)element->content;
		point->color = rgba_to_int(rand() % 255,
			rand() % 255,
			rand() % 255, 0);
		element = element->next;
	}
}

int		calc_gradient(int color1, int color2, double stage)
{
	int		color;
	int		r;
	int		g;
	int		b;

	r = (int)(((color1 >> 16) & 0xFF) +
			(((color2 >> 16) & 0xFF) - ((color1 >> 16) & 0xFF)) * stage) << 16;
	g = (int)(((color1 >> 8) & 0xFF) +
			(((color2 >> 8) & 0xFF) - ((color1 >> 8) & 0xFF)) * stage) << 8;
	b = (int)((color1 & 0xFF) +
			((color2 & 0xFF) - (color1 & 0xFF)) * stage);
	color = r | g | b;
	return (color);
}
