/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 00:48:06 by cababou           #+#    #+#             */
/*   Updated: 2018/09/11 22:37:13 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_button	*create_button(t_params *p, char *text, t_point *loc, t_point *co)
{
	t_button *button;

	if ((button = malloc(sizeof(t_button))) == NULL)
		exit_program(p, 1);
	button->button_text = text;
	button->location = loc;
	button->size = new_fpt(p, 180, 45, 10);
	button->color = co->x;
	button->text_color = co->y;
	button->is_visible = 1;
	button->status = 0;
	button->need_redraw = 0;
	free(co);
	return (button);
}

void		make_button(t_params *p, t_button *button, t_lstcontainer *cnt,
			int (*callback)(t_params *p, t_button *button,
			t_point *click_loc, int click))
{
	button->click_call = callback;
	button->identifier = p->next_indentifier++;
	lstcontainer_add(cnt, button);
}

void		render_button(t_params *p, t_button *b)
{
	fill_rect(p, dup_pt(p, b->location), dup_pt(p, b->size), b->color);
	mlx_string_put(p->mlx, p->fdf_window->window,
	b->location->x + b->size->x / 2 - textsize(b->button_text) / 2,
	b->location->y + b->size->z, b->text_color, b->button_text);
}
