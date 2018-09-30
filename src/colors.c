/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:05:14 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 02:41:13 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		calc_gradient(int color1, int color2, double stage)
{
	int		color;
	int		r;
	int		g;
	int		b;

	r = (int)(((color1 >> 16) & 0xFF) +
			(((color2 >> 16) & 0xFF) - ((color1 >> 16) & 0xFF)) * stage) << 16;
	g = (int)(((color1 >> 8) & 0xFF) +
			(((color1 >> 8) & 0xFF) - ((color1 >> 8) & 0xFF)) * stage) << 8;
	b = (int)(((color1) & 0xFF) +
			(((color1) & 0xFF) - (color1 & 0xFF)) * stage);
	color = r | g | b;
	return (color);
}

void	generate_colors(t_window *w)
{
	int *colors;
	int	last_color;
	int i;

	if (w->colors != NULL)
	{
		free(w->colors);
		w->colors = NULL;
	}
	if ((colors = malloc(sizeof(int) * w->max_iteration)) == NULL)
		handle_error(ERR_MEMORY, 1);
	ft_bzero(colors, sizeof(int) * w->max_iteration);
	i = 0;
	while (i < w->max_iteration)
	{
		if (i % 10 == 0)
		{
			colors[i] = rgba_to_int(rand() * 255, rand() * 255, rand() * 255, 0);
			last_color = colors[i];
		}
		i++;
	}
	colors[i - 1] = rgba_to_int(rand() * 255, rand() * 255, rand() * 255, 0);
	i = 1;
	last_color = colors[0];
	while (i < w->max_iteration)
	{
		if (i % 10 == 0)
		{
			last_color = colors[i];
			i++;
			continue ;
		}
		colors[i] = calc_gradient(last_color, (i + (10 - i % 10)) >= w->max_iteration ? colors[w->max_iteration - 1] : colors[i + (10 - i % 10)], ((double)(i % 10)) / 10);
		i++;
	}
	colors[w->max_iteration - 1] = 0;
	w->colors = colors;
}
