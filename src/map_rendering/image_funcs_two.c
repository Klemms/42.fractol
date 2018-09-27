/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_funcs_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 02:54:26 by cababou           #+#    #+#             */
/*   Updated: 2018/09/17 21:43:52 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void		destroy_image(t_params *p, void *image, t_image *img)
{
	mlx_destroy_image(p->mlx, image);
	free(img);
}

void		is_point_valid(t_params *p, char *filepath, char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == ',')
			return ;
		if (str[i] < '0' || str[i] > '9')
		{
			ft_putstr("This is not a valid fdf file (");
			ft_putstr(filepath);
			ft_putendl(")");
			exit_program(p, 0);
		}
		i++;
	}
}

t_lanorme	*make_lanorme(t_params *p)
{
	t_lanorme *lanorme;

	if ((lanorme = malloc(sizeof(t_lanorme))) == NULL)
		exit_program(p, 1);
	return (lanorme);
}

t_lanorme	*set_lanorme(t_params *p, t_lstcontainer *pt, t_point *pp, char *fp)
{
	p->fdf_window->lanorme->points = pt;
	p->fdf_window->lanorme->pt = pp;
	p->fdf_window->lanorme->fp = fp;
	return (p->fdf_window->lanorme);
}
