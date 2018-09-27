/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 15:34:57 by cababou           #+#    #+#             */
/*   Updated: 2018/09/03 01:39:50 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int				file_max_x(t_lstcontainer *points)
{
	t_list		*element;
	t_point		*point;
	int			max_x;

	element = points->firstelement;
	max_x = 0;
	while (element)
	{
		point = (t_point *)element->content;
		max_x = point->x > max_x ? point->x : max_x;
		element = element->next;
	}
	return (max_x);
}

int				file_max_y(t_lstcontainer *points)
{
	return (((t_point *)ft_lstgetlast(points->firstelement)->content)->y);
}

int				file_height(t_lstcontainer *points)
{
	t_list	*element;
	t_point	*point;
	int		min_z;
	int		max_z;

	element = points->firstelement;
	min_z = 0;
	max_z = 0;
	while (element)
	{
		point = (t_point *)element->content;
		min_z = point->z < min_z ? point->z : min_z;
		max_z = point->z > max_z ? point->z : max_z;
		element = element->next;
	}
	return (max_z - min_z);
}

t_lstcontainer	*base_lines(t_params *p, t_lstcontainer *points)
{
	t_lstcontainer	*lines;
	t_point			*last_point;
	t_list			*point;
	t_point			*current_point;

	if ((lines = lstcontainer_new()) == NULL)
		exit_program(p, 0);
	point = points->firstelement;
	last_point = NULL;
	while (point)
	{
		current_point = (t_point *)point->content;
		if (last_point)
		{
			if (current_point->y == last_point->y)
				lstcontainer_add(lines,
					new_line(p, last_point, current_point));
		}
		last_point = current_point;
		point = point->next;
	}
	return (lines);
}

t_lstcontainer	*make_lines(t_params *p, t_lstcontainer *points)
{
	t_lstcontainer	*lines;
	t_list			*element;
	int				max_x;
	int				i;
	int				size;

	lines = base_lines(p, points);
	max_x = file_max_x(points);
	i = 0;
	size = lstcontainer_size(points);
	element = points->firstelement;
	while (i < size - max_x - 1)
	{
		lstcontainer_add(lines, new_line(p,
			(t_point *)element->content,
			(t_point *)ft_lstget_fromelement(i + max_x + 1,
				element)->content));
		element = element->next;
		i++;
	}
	return (lines);
}
