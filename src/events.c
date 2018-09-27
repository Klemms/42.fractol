/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 22:43:03 by cababou           #+#    #+#             */
/*   Updated: 2018/09/10 15:44:53 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_motion(int x, int y, t_params *p)
{
	if (p->fdf_window->tabs && p->fdf_window->left_click_pressed)
	{
		p->fdf_window->tabs->selected_tab->map_settings->rot_z =
		constrain_angle(p->fdf_window->tabs->selected_tab->map_settings->rot_z +
			(p->fdf_window->last_x - x) / 2);
		p->fdf_window->tabs->selected_tab->map_settings->rot_x =
		constrain_angle(p->fdf_window->tabs->selected_tab->map_settings->rot_x +
			(p->fdf_window->last_y - y) / 2);
		hide_tab(p, p->fdf_window->tabs->selected_tab);
		render_tab(p, p->fdf_window->tabs->selected_tab);
	}
	p->fdf_window->last_x = x;
	p->fdf_window->last_y = y;
	return (0);
}
