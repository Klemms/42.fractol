/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 02:26:59 by cababou           #+#    #+#             */
/*   Updated: 2018/09/28 07:18:33 by cababou          ###   ########.fr       */
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

double test(int v1, int v2, int width, int x)
{
	double	range;
	double	percent;

	range = v2 - v1;
	percent = ((double)x) / width;
	return (range * percent);
}

void	distance_to_center(t_window *w, int x, int y)
{
	int dist_x;
	int dist_y;

	dist_x = x - w->width / 2;
	dist_x = y - w->height / 2;





	printf("%d ** %d\n", x - w->width / 2, y - w->height / 2);
}

int		mouse_release(int button, int x, int y, t_window *w)
{
	distance_to_center(w, x, y);
	if (button == 1)
	{
		w->zoom_x *= 1.1;
		w->zoom_y *= 1.1;
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
	}
	if (button == 2)
	{
		w->zoom_x *= 0.9;
		w->zoom_y *= 0.9;
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
	}
	printf("%f\n", test(w->x2, w->x1, w->width, x));
	w->x1 = w->x1 + test(w->x2, w->x1, w->width, x);
	w->x2 = w->x2 + test(w->x2, w->x1, w->width, x);
	w->y1 = w->y1 + test(w->y2, w->y1, w->height, y);
	w->y2 = w->y2 + test(w->y2, w->y1, w->height, y);
	return (1);
}

int		key_press(int key, t_window *w)
{
	ft_putnbr(key);
	ft_putendl("");
	if (key == 53)
		exit_program(0);
	return (1);
}

int		close_window(t_window *w)
{
	w->is_closed = 1;
	*w->need_check = 1;
	mlx_destroy_window(w->mlx, w->window);
	return (1);
}
