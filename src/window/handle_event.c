/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 02:26:59 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 04:52:06 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include <stdio.h>

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

void	dezoom_1(t_window *w, int x, int y)
{
	long double xmouse;
	long double ymouse;
	long double xminprime;
	long double yminprime;

	xmouse = w->x1 + (x * (w->x2 - w->x1)) / w->width;
	ymouse = w->y1 + (y * (w->y2 - w->y1)) / w->height;
	xminprime = w->x1 + (xmouse - (((w->x2 - w->x1)) / 4));
	printf("%Lf ** %Lf\n", w->x1, xminprime);
	printf("%Lf", w->x2);
	w->x2 = w->x2 + ((w->x2 - w->x1) / 2) + xminprime;
	printf(" ** %Lf\n", w->x2);
	fflush(stdout);
	/*yminprime = ymouse - (((w->y2 - w->y1)) / 4);
	w->y2 = ((w->y2 - w->y1) / 2) + yminprime;*/
	w->x1 = xminprime;
	//w->y1 = yminprime;
}

int		mouse_press(int button, int x, int y, t_window *w)
{
	if (button == 1)
	{
		zoom_2(w, x, y);
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
		render_iterations(w);
	}
	if (button == 2)
	{
		dezoom_1(w, x, y);
		//w->max_iteration *= 1.1;
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
		render_iterations(w);
	}
	return (1);
}

int		mouse_release(int button, int x, int y, t_window *w)
{
	if (button == 1)
	{
		zoom_2(w, x, y);
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
		render_iterations(w);
	}
	if (button == 2)
	{
		dezoom_1(w, x, y);
		//w->max_iteration *= 1.1;
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
		render_iterations(w);
	}
	return (1);
}

int		key_press(int key, t_window *w)
{
	ft_putnbr(key);
	ft_putendl("");
	if (key == 53)
		exit_program(0);
	if (key == 69 || key == 116)
	{
		w->max_iteration += key == 69 ? 10 : 1;
		generate_colors(w);
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
		render_iterations(w);
	}
	if (key == 78 || key == 121)
	{
		w->max_iteration -= key == 78 ? 10 : 1;
		generate_colors(w);
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
		render_iterations(w);
	}
	if (key == 8)
	{
		generate_colors(w);
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
		render_iterations(w);
	}
	if (key == 15)
	{
		w->max_iteration = 75;
		generate_colors(w);
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_init(w);
		render_iterations(w);
	}
	return (1);
}

int		close_window(t_window *w)
{
	w->is_closed = 1;
	*w->need_check = 1;
	mlx_destroy_window(w->mlx, w->window);
	return (1);
}
