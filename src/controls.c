/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 07:00:39 by cababou           #+#    #+#             */
/*   Updated: 2018/09/28 07:05:33 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double test(int v1, int v2, int width, int x)
{
	double	range;
	double	percent;

	range = v2 - v1;
	percent = ((double)x) / width;
	return (range * percent);
}
