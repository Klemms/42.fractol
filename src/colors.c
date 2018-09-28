/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:05:14 by cababou           #+#    #+#             */
/*   Updated: 2018/09/28 06:20:09 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		calc_gradient(int color1, int color2, double stage)
{
	int		color;
	int		r;
	int		g;
	int		b;

	r = (int)(((color1 >> 16) & 0xFF) +
			(((color2 >> 16) & 0xFF) - ((color1 >> 16) & 0xFF)) * stage) << 16;
	g = (int)(((color1 >> 8) & 0xFF) +
			(((color2 >> 8) & 0xFF) - ((color1 >> 8) & 0xFF)) * stage) << 8;
	b = (int)((color1 & 0xFF) +
			((color2 & 0xFF) - (color1 & 0xFF)) * stage);
	color = r | g | b;
	return (color);
}

void	generate_colors(t_window *w, int far, int mid, int near)
{
	int *colors;
	int i;

	if (w->colors != NULL)
	{
		free(w->colors);
		w->colors = NULL;
	}
	if ((colors = malloc(sizeof(int) * w->max_iteration)) == NULL)
		handle_error(ERR_MEMORY, 1);
	i = 0;
	while (i < w->max_iteration / 2)
	{
		colors[i] = calc_gradient(far, mid, ((double)i) / w->max_iteration);
		i++;
	}
	while (i < w->max_iteration)
	{
		colors[i] = calc_gradient(mid, near, ((double)i) / w->max_iteration);
		i++;
	}
	w->colors = colors;
}
