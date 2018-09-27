/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_nb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 04:25:25 by cababou           #+#    #+#             */
/*   Updated: 2018/09/17 21:03:23 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*set_point_color(t_point *p, int color)
{
	p->color = color;
	return (p);
}

t_point	*set_point(t_point *p, int x, int y, int z)
{
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

double	to_radians(int degrees)
{
	return (degrees * (M_PI / 180.0));
}

t_point	*add_color(t_point *p, int color)
{
	p->color = color;
	return (p);
}

int		highest_z(t_point *start, t_point *end)
{
	return (start->z > end->z ? start->z : end->z);
}
