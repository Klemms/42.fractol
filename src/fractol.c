/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 01:27:54 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 04:50:38 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <time.h>

void	exit_program(int code)
{
	ft_putendl("Exiting Fractol.");
	exit(code);
}

void	start(t_params *p)
{
	t_list		*el;
	t_window	*window;

	el = p->windows->firstelement;
	while (el)
	{
		window = (t_window *)el->content;
		if (window->fractal_type == FRACTAL_MANDELBROT)
			mandelbrot_init(window);
		el = el->next;
	}
}

void	render_iterations(t_window *w)
{
	char	*iter;
	char	*str;

	iter = ft_itoa(w->max_iteration);
	str = ft_strjoin("Iterations : ", iter, 0);
	mlx_string_put(w->mlx, w->window, 15, 15, BLACK_COLOR, iter);
	free(iter);
	free(str);
}

void	register_events(t_params *p)
{
	t_list		*el;
	t_window	*window;

	el = p->windows->firstelement;
	while (el)
	{
		window = (t_window *)el->content;
		mlx_hook(window->window, DestroyNotify, NoEventMask,
			close_window, window);
		mlx_hook(window->window, KeyPress, KeyPressMask,
			key_press, window);
		mlx_hook(window->window, ButtonRelease, ButtonReleaseMask,
			mouse_release, window);
		mlx_hook(window->window, ButtonPress, ButtonPressMask,
			mouse_press, window);
		el = el->next;
	}
}

int		main(int argc, char **argv)
{
	t_params	*p;

	if (argc <= 1)
		handle_error(ERR_NOT_ENOUGH_ARGS, 1);
	if ((p = malloc(sizeof(t_params))) == NULL
		|| (p->windows = lstcontainer_new()) == NULL)
		handle_error(ERR_MEMORY, 1);
	if ((p->mlx = mlx_init()) == NULL)
		handle_error(ERR_MLX_INIT, 1);
	p->need_check = 0;
	init_windows(p, argc, argv);
	mlx_loop_hook(p->mlx, loop_program, p);
	register_events(p);
	srand(time(NULL));
	start(p);
	mlx_loop(p->mlx);
	return (0);
}
