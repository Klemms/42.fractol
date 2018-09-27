/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:49:18 by cababou           #+#    #+#             */
/*   Updated: 2018/09/16 01:34:39 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map_settings	*make_map_settings(t_params *p, t_lstcontainer *points)
{
	t_map_settings	*map_settings;

	if ((map_settings = malloc(sizeof(t_map_settings))) == NULL)
		exit_program(p, 1);
	map_settings->isometric_factor = -2;
	map_settings->size = 2;
	map_settings->height_size = 1;
	map_settings->x_position = p->fdf_window->width / 2;
	map_settings->y_position = p->fdf_window->height / 2;
	map_settings->rot_x = 320;
	map_settings->rot_y = 335;
	map_settings->rot_z = 330;
	map_settings->angle_1 = 0;
	map_settings->angle_2 = 180;
	map_settings->max_x = file_max_x(points);
	map_settings->max_y = file_max_y(points);
	map_settings->height = file_height(points);
	return (map_settings);
}

t_dline			*new_line(t_params *p, t_point *start, t_point *end)
{
	t_dline	*line;

	if ((line = malloc(sizeof(t_dline))) == NULL)
		exit_program(p, 1);
	line->start = start;
	line->end = end;
	if ((line->is_rendered = malloc(sizeof(t_int))) == NULL)
		exit_program(p, 1);
	line->is_rendered->value = 0;
	return (line);
}

t_point			*add_fpt(t_point *point, int x, int y, int z)
{
	point->x += x;
	point->y += y;
	point->z += z;
	return (point);
}

t_point			*new_fpt(t_params *p, int x, int y, int z)
{
	t_point	*point;

	if ((point = malloc(sizeof(t_point))) == NULL)
		exit_program(p, 1);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = -1;
	return (point);
}

t_point			*new_pt(t_params *p, int x, int y)
{
	return (new_fpt(p, x, y, 0));
}
