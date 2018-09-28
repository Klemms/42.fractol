/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 02:26:59 by cababou           #+#    #+#             */
/*   Updated: 2018/09/28 08:10:36 by cababou          ###   ########.fr       */
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

void	distance_to_center(t_window *w, int x, int y)
{
	long double x_mult;
	long double y_mult;

	x_mult = 1 + 0.5 * (((double)x - w->width / 2) / (w->width / 2));
	y_mult = 1 + 0.5 * (((double)y - w->height / 2) / (w->height / 2));
	printf("%Lf\n", (w->x2 - w->x1) * x_mult - (w->x2 - w->x1));
	printf("%Lf ** %Lf ** %Lf ** %Lf\n", w->x1, w->x2, w->y1, w->y2);
	fflush(stdout);
	w->x1 += (w->x2 - w->x1) * x_mult - (w->x2 - w->x1);
	w->x2 += (w->x2 - w->x1) * x_mult - (w->x2 - w->x1);
	w->y1 += (w->y2 - w->y1) * y_mult - (w->y2 - w->y1);
	w->y2 += (w->y2 - w->y1) * y_mult - (w->y2 - w->y1);
	printf("%Lf ** %Lf ** %Lf ** %Lf\n", w->x1, w->x2, w->y1, w->y2);
	fflush(stdout);
}

int		mouse_release(int button, int x, int y, t_window *w)
{
	//distance_to_center(w, x, y);
	if (button == 1)
	{
		w->x1 = x - w->height;
		w->x2 = x + w->height;

		w->y1 = y - w->height;
		w->y2 = y + w->height;

		/*w->zoom_x = (w->width / (w->x2 - w->x1));
		w->zoom_y = (w->height / (w->y2 - w->y1));*/
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
	}
	if (button == 2)
	{
		/*w->zoom_x *= 0.9;
		w->zoom_y *= 0.9;*/
		if (w->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_render(w);
	}
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
