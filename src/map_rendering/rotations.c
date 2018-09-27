/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 22:58:58 by cababou           #+#    #+#             */
/*   Updated: 2018/09/17 00:44:31 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_point	*rotate(t_params *p, t_point *point, t_point *rot)
{
	return (
		z_rotation(p,
		y_rotation(p,
		x_rotation(p, point, rot->x), rot->y), rot->z));
}

int		constrain_angle(int x)
{
	if (x >= 0 && x < 360)
		return (x);
	x = fmod(x, 359);
	if (x < 0)
		x += 359;
	return (x);
}

t_point	*x_rotation(t_params *p, t_point *point, int angle)
{
	int y;

	y = point->y;
	point->y = y * p->fdf_window->cos_table[constrain_angle(angle)]
		- point->z * p->fdf_window->sin_table[constrain_angle(angle)];
	point->z = y * p->fdf_window->sin_table[constrain_angle(angle)]
		+ point->z * p->fdf_window->cos_table[constrain_angle(angle)];
	return (point);
}

t_point	*y_rotation(t_params *p, t_point *point, int angle)
{
	int x;

	x = point->x;
	point->x = point->z * p->fdf_window->sin_table[constrain_angle(angle)]
		+ x * p->fdf_window->cos_table[constrain_angle(angle)];
	point->z = point->z * p->fdf_window->cos_table[constrain_angle(angle)]
		- x * p->fdf_window->sin_table[constrain_angle(angle)];
	return (point);
}

t_point	*z_rotation(t_params *p, t_point *point, int angle)
{
	int x;

	x = point->x;
	point->x = x * p->fdf_window->cos_table[constrain_angle(angle)]
		- point->y * p->fdf_window->sin_table[constrain_angle(angle)];
	point->y = x * p->fdf_window->sin_table[constrain_angle(angle)]
		+ point->y * p->fdf_window->sin_table[constrain_angle(angle)];
	return (point);
}
