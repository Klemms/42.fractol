/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 06:35:27 by cababou           #+#    #+#             */
/*   Updated: 2018/09/02 00:17:39 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_cos_table(t_params *p)
{
	int i;

	if ((p->fdf_window->cos_table = malloc(sizeof(double) * 361)) == NULL)
		exit_program(p, 1);
	i = 0;
	while (i < 360)
	{
		p->fdf_window->cos_table[i] = cos(to_radians(i));
		i++;
	}
}

void	make_sin_table(t_params *p)
{
	int i;

	if ((p->fdf_window->sin_table = malloc(sizeof(double) * 361)) == NULL)
		exit_program(p, 1);
	i = 0;
	while (i < 360)
	{
		p->fdf_window->sin_table[i] = sin(to_radians(i));
		i++;
	}
}
