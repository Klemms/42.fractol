/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 02:04:42 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 02:45:59 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			str_to_fractal(char *string)
{
	if (ft_strequ(string, "mandelbrot"))
		return (FRACTAL_MANDELBROT);
	ft_putstr("No Fractal found with name '");
	ft_putstr(string);
	ft_putendl("'. Using mandelbrot");
	return (FRACTAL_MANDELBROT);
}

t_window	*make_window(t_params *p, char *title, int fractal_type)
{
	t_window	*window;

	if ((window = malloc(sizeof(t_window))) == NULL)
		handle_error(ERR_MEMORY, 1);
	if ((window->window = mlx_new_window(p->mlx, 1200, 1200, title)) == NULL)
		handle_error(ERR_MLX_INIT_WINDOW, 1);
	window->mlx = p->mlx;
	window->width = 1200;
	window->height = 1200;
	window->size = window->width * window->height;
	window->fractal_type = fractal_type;
	window->is_closed = 0;
	window->need_check = &(p->need_check);
	window->max_iteration = 75;
	window->colors = NULL;
	return (window);
}

void		init_windows(t_params *p, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		lstcontainer_add(p->windows,
			make_window(p, argv[i], str_to_fractal(argv[i])));
		i++;
	}
}
