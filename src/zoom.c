/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 04:51:05 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 05:10:07 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_center(t_window *w, int x, int y)
{
	long double xmouse;
	long double ymouse;
	long double xminprime;
	long double yminprime;

	xmouse = w->x1 + (x * (w->x2 - w->x1)) / w->width;
	ymouse = w->y1 + (y * (w->y2 - w->y1)) / w->height;
	xminprime = xmouse - (((w->x2 - w->x1)) / 4);
	w->x2 = ((w->x2 - w->x1) / 2) + xminprime;
	yminprime = ymouse - (((w->y2 - w->y1)) / 4);
	w->y2 = ((w->y2 - w->y1) / 2) + yminprime;
	w->x1 = xminprime;
	w->y1 = yminprime;
}

void	zoom_mouse(t_window *w, double x, double y)
{
	long double xmouse;
	long double ymouse;

	xmouse = w->x1 + (x * (w->x2 - w->x1)) / w->width;
	ymouse = w->y1 + (y * (w->y2 - w->y1)) / w->height;
	w->x1 = xmouse - (((w->x1 - xmouse) * -1) / 2);
	w->x2 = xmouse + ((w->x2 - xmouse) / 2);
	w->y1 = ymouse - (((w->y1 - ymouse) * -1) / 2);
	w->y2 = ymouse + ((w->y2 - ymouse) / 2);
	ft_putendl("testttsts");
}

void	unzoom_mouse(t_window *w, double x, double y)
{
	long double xmouse;
	long double ymouse;

	xmouse = w->x1 + (x * (w->x2 - w->x1)) / w->width;
	ymouse = w->y1 + (y * (w->y2 - w->y1)) / w->height;
	w->x1 = xmouse - (((w->x1 - xmouse) * -1) * 2);
	w->x2 = xmouse + ((w->x2 - xmouse) * 2);
	w->y1 = ymouse - (((w->y1 - ymouse) * -1) * 2);
	w->y2 = ymouse + ((w->y2 - ymouse) * 2);
}

void	re_render(t_window *w)
{
	if (w->fractal_type == FRACTAL_MANDELBROT)
		mandelbrot_init(w);
	render_iterations(w);
}
