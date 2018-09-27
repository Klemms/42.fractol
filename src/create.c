/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:04:16 by cababou           #+#    #+#             */
/*   Updated: 2018/09/02 00:15:26 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_window	*create_window_struct(t_params *p, int width, int height, char *t)
{
	t_window	*window;

	if ((window = malloc(sizeof(t_window))) == NULL)
		exit_program(p, 1);
	window->width = width;
	window->height = height;
	window->size = new_pt(p, width, height);
	window->title = t;
	window->last_x = 0;
	window->last_y = 0;
	window->left_click_pressed = 0;
	window->tabs = NULL;
	window->line = NULL;
	window->window = NULL;
	window->sin_table = NULL;
	window->cos_table = NULL;
	return (window);
}
