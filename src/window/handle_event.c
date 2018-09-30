/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 02:26:59 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 07:29:14 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		loop_program(t_params *p)
{
	t_list		*el;
	t_window	*window;
	int			window_open;

	if (p->need_check)
	{
		window_open = 0;
		el = p->windows->firstelement;
		while (el)
		{
			window = (t_window *)el->content;
			if (!window->is_closed)
				window_open = 1;
			el = el->next;
		}
		if (!window_open)
			exit_program(0);
		p->need_check = 0;
	}
	return (1);
}

int		mouse_press(int button, int x, int y, t_window *w)
{
	if (button == 4)
	{
		zoom_mouse(w, x, y);
		re_render(w);
	}
	if (button == 5)
	{
		unzoom_mouse(w, x, y);
		re_render(w);
	}
	return (1);
}

int		mouse_release(int button, int x, int y, t_window *w)
{
	if (button == 1)
	{
		zoom_center(w, x, y);
		re_render(w);
	}
	if (button == 2)
	{
		re_render(w);
	}
	return (1);
}

int		key_press(int key, t_window *w)
{
	if (key == 53)
		exit_program(0);
	if (key == 123 || key == 124 || key == 125 || key == 126)
		handle_arrows(w, key);
	if (key == 78 || key == 121 || key == 69 || key == 116)
		handle_iterations(key, w);
	if (key == 8)
	{
		generate_colors(w);
		re_render(w);
	}
	if (key == 15)
	{
		w->max_iteration = 75;
		generate_colors(w);
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_init(w);
		if (w->fractal_type == FRACTAL_JULIA)
			julia_init(w);
		if (w->fractal_type == FRACTAL_SHIP)
			ship_init(w);
		render_iterations(w);
	}
	if (key == 17)
		w->mouse_enabled = !w->mouse_enabled;
	return (1);
}

int		close_window(t_window *w)
{
	w->is_closed = 1;
	*w->need_check = 1;
	mlx_destroy_window(w->mlx, w->window);
	return (1);
}
