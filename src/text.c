/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 00:44:33 by cababou           #+#    #+#             */
/*   Updated: 2018/09/11 22:31:25 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		textsize(char *text)
{
	return (ft_strlen(text) * 10);
}

t_point	*dup_pt(t_params *p, t_point *pt)
{
	t_point *npt;

	npt = new_fpt(p, pt->x, pt->y, pt->z);
	npt->color = pt->color;
	return (npt);
}
