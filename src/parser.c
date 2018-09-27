/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 23:29:48 by cababou           #+#    #+#             */
/*   Updated: 2018/09/17 21:42:57 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			handle_open_error(t_params *p, char *fp, t_lstcontainer *points)
{
	ft_lstdel(points->firstelement, 1);
	free(points);
	if (errno == EACCES || errno == EFAULT)
	{
		ft_putstr("Couldn't open a file, missing permissions. (");
		ft_putstr(fp);
		ft_putendl(")");
	}
	else
	{
		ft_putstr("Couldn't open a file. (");
		ft_putstr(fp);
		ft_putendl(")");
	}
	exit_program(p, 0);
}

void			parse_file2(t_params *p, t_lanorme *l)
{
	t_lstcontainer	*li;

	l->pt->x = 0;
	if ((li = ft_strsplit_lst((*l->tmp), ' ', '\n', '\0')) == NULL)
		exit_program(p, 1);
	while (l->pt->x < lstcontainer_fastsize(li))
	{
		is_point_valid(p, l->fp,
			ft_lstget(l->pt->x, li->firstelement)->content);
		lstcontainer_add(l->points, new_fpt(p, l->pt->x, l->pt->y,
			ft_atoi((char *)ft_lstget(l->pt->x, li->firstelement)->content)));
		((t_point *)l->points->lastelement->content)->color = ft_hex_to_color(
			ft_strsplitone(
				ft_lstget(l->pt->x, li->firstelement)->content, ',', 1), 1);
		if (((t_point *)l->points->lastelement->content)->color == 0)
			((t_point *)l->points->lastelement->content)->color = -1;
		l->pt->x++;
	}
	ft_lstdel(li->firstelement, 1);
	if (lstcontainer_fastsize(li) > 0)
		l->pt->y++;
	free(li);
	free(*(l->tmp));
	(*l->tmp) = NULL;
}

void			parse_file_end(t_params *p, t_point *pt, char *fp)
{
	if (pt->z == -1)
	{
		ft_putstr("Couldn't read a file. (");
		ft_putstr(fp);
		ft_putendl(")");
		exit_program(p, 0);
	}
}

t_lstcontainer	*parse_file(t_params *p, char *fp)
{
	t_lstcontainer	*points;
	int				fd;
	t_point			*pt;
	char			*tmp;

	if ((points = lstcontainer_new()) == NULL)
		exit_program(p, 1);
	fd = open(fp, O_RDONLY);
	if (fd < 0)
		handle_open_error(p, fp, points);
	tmp = NULL;
	pt = new_pt(p, 0, 0);
	while ((pt->z = get_next_line(fd, &tmp)) == 1)
	{
		set_lanorme(p, points, pt, fp);
		p->fdf_window->lanorme->tmp = &tmp;
		parse_file2(p, p->fdf_window->lanorme);
	}
	parse_file_end(p, pt, fp);
	free(pt);
	return (points);
}
