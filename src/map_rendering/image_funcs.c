/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 02:54:26 by cababou           #+#    #+#             */
/*   Updated: 2018/09/17 20:56:48 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_mlx_img	*new_mlx_img(t_params *p)
{
	t_mlx_img	*mlx_img;

	if ((mlx_img = malloc(sizeof(t_mlx_img))) == NULL)
		exit_program(p, 1);
	return (mlx_img);
}

t_image		*new_image(t_params *p, int width, int height, unsigned int *img)
{
	t_image	*image;

	if ((image = malloc(sizeof(t_image))) == NULL)
		exit_program(p, 1);
	image->width = width;
	image->height = height;
	image->image = img;
	return (image);
}

void		write_pxl(t_image *img, int x, int y, int color)
{
	if (x > 0 && x < img->width && y > 0 && y < img->height)
		img->image[x + img->width * y] = color;
}

int			is_file_valid_2(t_lstcontainer *points, t_list *tmp, int x)
{
	int		last_x;

	last_x = -1;
	while (tmp)
	{
		if (((t_point *)tmp->content)->x > x ||
		(last_x < x && ((t_point *)tmp->content)->x <= last_x))
			return (0);
		last_x = ((t_point *)tmp->content)->x;
		if (((t_point *)tmp->content)->x != x && tmp == points->lastelement)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int			is_file_valid(t_lstcontainer *points)
{
	int		x;
	t_list	*tmp;

	if (points == NULL || points->firstelement == NULL)
		return (0);
	x = -1;
	tmp = points->firstelement;
	while (tmp && ((t_point *)tmp->content)->x > x)
	{
		x = ((t_point *)tmp->content)->x;
		tmp = tmp->next;
	}
	if (x == 0)
		return (1);
	tmp = points->firstelement;
	return (is_file_valid_2(points, tmp, x));
}
