/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 15:09:55 by cababou           #+#    #+#             */
/*   Updated: 2018/09/17 00:43:55 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>

void				zoom_map(t_params *p, int factor)
{
	if (factor != 0)
	{
		p->fdf_window->tabs->selected_tab->map_settings->size += factor;
		hide_tab(p, p->fdf_window->tabs->selected_tab);
		render_tab(p, p->fdf_window->tabs->selected_tab);
	}
}

void				render_infos(t_params *p, t_tab *tab)
{
	int x;
	int y;

	(void)p;
	(void)tab;
	x = 15;
	y = p->fdf_window->height - 26 - 225 - 15;
	mlx_put_image_to_window(p->mlx, p->fdf_window->window,
		p->fdf_window->infos_back_img, x, y);
	mlx_string_put(p->mlx, p->fdf_window->window,
		x + 15, y + 10, BLACK_COLOR, tab->tab_name);
	mlx_string_put(p->mlx, p->fdf_window->window, x + 15, y + 40,
		BLACK_COLOR, tab->is_tab_valid ? "Valid file" : "Invalid file");
	mlx_string_put(p->mlx, p->fdf_window->window,
		x + 15, y + 225 - 115, BLACK_COLOR, "Left Click + Drag > Rotate");
	mlx_string_put(p->mlx, p->fdf_window->window,
		x + 15, y + 225 - 95, BLACK_COLOR, "Mouse Wheel > Zoom In/Out");
	mlx_string_put(p->mlx, p->fdf_window->window,
		x + 15, y + 225 - 75, BLACK_COLOR, "+/- > Change Height Factor");
	mlx_string_put(p->mlx, p->fdf_window->window,
		x + 15, y + 225 - 55, BLACK_COLOR, "P > Toggle Auto-Rotation");
	mlx_string_put(p->mlx, p->fdf_window->window,
		x + 15, y + 225 - 35, BLACK_COLOR, "R > Randomize Colors");
}

static inline void	render_map2(t_params *p, t_list *e, t_tab *t, t_image *img)
{
	t_map_settings	*ms;
	t_dline			*dl;

	ms = t->map_settings;
	dl = (t_dline *)e->content;
	init_line(p,
	add_fpt(two_d_to_three_d(p, rotate(p,
		set_point_color(
		set_point(t->render_p1, (dl->start->x - ms->max_x / 2) * ms->size,
		(dl->start->y - ms->max_y / 2) * ms->size,
		dl->start->z * ms->height_size * ms->size), dl->start->color),
		set_point(t->render_rot, ms->rot_x, ms->rot_y, ms->rot_z)),
		ms->angle_1, ms->angle_2), ms->x_position, ms->y_position, 0),
	add_fpt(two_d_to_three_d(p, rotate(p,
		set_point_color(
		set_point(t->render_p2, (dl->end->x - ms->max_x / 2) * ms->size,
		(dl->end->y - ms->max_y / 2) * ms->size,
		dl->end->z * ms->height_size * ms->size), dl->end->color),
		set_point(t->render_rot, ms->rot_x, ms->rot_y, ms->rot_z)),
		ms->angle_1, ms->angle_2), ms->x_position, ms->y_position, 0));
	line(p, img);
}

void				render_map(t_params *p, t_tab *tab)
{
	t_list			*element;
	t_image			*image;
	t_mlx_img		*mlx_img;

	element = tab->lines->firstelement;
	tab->map_image = mlx_new_image(p->mlx, p->fdf_window->width,
		p->fdf_window->height - 65);
	mlx_img = new_mlx_img(p);
	image = new_image(p, p->fdf_window->width, p->fdf_window->height - 65,
		(unsigned int *)mlx_get_data_addr(tab->map_image,
		&mlx_img->bits_per_pixel, &mlx_img->size_line, &mlx_img->endian));
	while (element)
	{
		render_map2(p, element, tab, image);
		element = element->next;
	}
	mlx_put_image_to_window(p->mlx, p->fdf_window->window,
		tab->map_image, 0, 65);
	destroy_image(p, tab->map_image, image);
	free(mlx_img);
	if (tab->show_info)
		render_infos(p, tab);
}
