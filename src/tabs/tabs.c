/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 00:14:43 by cababou           #+#    #+#             */
/*   Updated: 2018/09/17 21:32:22 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int		button_clicked(int click, int x, int y, t_params *p)
{
	t_list		*element;
	t_button	*button;

	element = p->fdf_window->tabs->buttons->firstelement;
	while (element)
	{
		button = (t_button *)element->content;
		if (button->is_visible)
		{
			if (x >= button->location->x &&
				x <= button->location->x + button->size->x &&
				y >= button->location->y &&
				y <= button->location->y + button->size->y)
				if (button->click_call(p, button, new_pt(p, x, y), click))
					return (0);
		}
		element = element->next;
	}
	return (0);
}

void	render_top_menu(t_params *p)
{
	t_list				*element;
	t_button			*button;

	fill_rect(p, new_pt(p, 0, 0),
	new_pt(p, p->fdf_window->width, 65), rgba_to_int(1, 163, 238, 0));
	mlx_string_put(p->mlx, p->fdf_window->window, 18, 21,
		rgba_to_int(135, 0, 114, 0), "FdF - cababou");
	fill_rect(p, new_pt(p, 180, 5), new_pt(p,
		p->fdf_window->width - 200, 55), rgba_to_int(0, 0, 0, 220));
	element = p->fdf_window->tabs->buttons->firstelement;
	while (element)
	{
		button = (t_button *)element->content;
		render_button(p, button);
		element = element->next;
	}
}
