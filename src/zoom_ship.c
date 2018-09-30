/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_ship.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 07:10:32 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 07:21:34 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	r_zoom_mouse(t_window *w, double x, double y)
{
	long double xmouse;
	long double ymouse;

	xmouse = w->x1 + (x * (w->x2 - w->x1)) / w->width;
	ymouse = w->y2 + (y * (w->y1 - w->y2)) / w->height;
	w->x1 = xmouse - (((w->x1 - xmouse) * -1) / 2);
	w->x2 = xmouse + ((w->x2 - xmouse) / 2);
	w->y2 = ymouse - (((w->y2 - ymouse) * -1) / 2);
	w->y1 = ymouse + ((w->y1 - ymouse) / 2);
}

void	r_zoom_center(t_window *w, double x, double y)
{
	long double xmouse;
	long double ymouse;
	long double xminprime;
	long double yminprime;

	xmouse = w->x1 + (x * (w->x2 - w->x1)) / w->width;
	ymouse = w->y2 + (y * (w->y1 - w->y2)) / w->height;
	xminprime = xmouse - (((w->x2 - w->x1)) / 4);
	w->x2 = ((w->x2 - w->x1) / 2) + xminprime;
	yminprime = ymouse - (((w->y1 - w->y2)) / 4);
	w->y1 = ((w->y1 - w->y2) / 2) + yminprime;
	w->x1 = xminprime;
	w->y2 = yminprime;
}

void	r_unzoom_mouse(t_window *w, double x, double y)
{
	long double xmouse;
	long double ymouse;

	xmouse = w->x1 + (x * (w->x2 - w->x1)) / w->width;
	ymouse = w->y2 + (y * (w->y1 - w->y2)) / w->height;
	w->x1 = xmouse - (((w->x1 - xmouse) * -1) * 2);
	w->x2 = xmouse + ((w->x2 - xmouse) * 2);
	w->y2 = ymouse - (((w->y2 - ymouse) * -1) * 2);
	w->y1 = ymouse + ((w->y1 - ymouse) * 2);
}
