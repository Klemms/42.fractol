/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 07:00:39 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 07:29:49 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_iterations(int key, t_window *w)
{
	if (key == 69 || key == 116)
	{
		w->max_iteration += key == 69 ? 10 : 1;
		generate_colors(w);
		re_render(w);
	}
	if (key == 78)
	{
		if (w->max_iteration > 12)
			w->max_iteration -= 10;
		else
			w->max_iteration = 2;
		generate_colors(w);
		re_render(w);
	}
	if (key == 121)
	{
		if (w->max_iteration > 2)
		{
			w->max_iteration -= 1;
			generate_colors(w);
			re_render(w);
		}
	}
}

int		mouse_motion(int x, int y, t_window *w)
{
	if (x >= 0 && x <= 1200 && y >= 0 && y <= 1200 && w->mouse_enabled)
	{
		w->mouse_p1 = (((double)(x % 1200)) / 1200 - 0.5) * 2;
		w->mouse_p2 = (((double)(y % 1200)) / 1200 - 0.5) * 2;
		re_render(w);
	}
	return (1);
}

void	handle_arrows(t_window *w, int key)
{
	long double rangeX;
	long double rangeY;

	rangeX = w->x2 - w->x1;
	rangeY = w->y2 - w->y1;
	if (key == 126)
		w->y1 += (rangeY * 0.1);
	if (key == 126)
		w->y2 += (rangeY * 0.1);
	if (key == 125)
		w->y1 -= (rangeY * 0.1);
	if (key == 125)
		w->y2 -= (rangeY * 0.1);
	if (key == 123)
		w->x1 += (rangeX * 0.1);
	if (key == 123)
		w->x2 += (rangeX * 0.1);
	if (key == 124)
		w->x1 -= (rangeX * 0.1);
	if (key == 124)
		w->x2 -= (rangeX * 0.1);
	re_render(w);
}

void	show_controls(void)
{
	ft_putendl("Controls :");
	ft_putendl("  R >> Reset to default view (Does not affect Julia's parameter)");
	ft_putendl("  C >> Randomize colors");
	ft_putendl("  Arrow Keys >> Move the fractal");
	ft_putendl("  Left Click >> Zoom and center on mouse position");
	ft_putendl("  Scroll Wheel >> Woom and Unzoom on mouse position");
	ft_putendl("  + and - (Numpad) >> Add 10 or remove 10 iterations (Also randomizes colors)");
	ft_putendl("  PageUp and PageDown >> Add 1 or remove 1 iteration (Also randomizes colors)");
	ft_putendl("  T >> Toggle mouse usage in Julia");
}
