/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 21:54:50 by cababou           #+#    #+#             */
/*   Updated: 2018/09/17 21:29:44 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		exit_program(t_params *p, int errortype)
{
	if (errortype == 0)
		ft_putendl("Exiting FdF.");
	if (errortype == 1)
		ft_putendl("Memory Error.");
	if (errortype == 2)
		ft_putendl("Failed to initialize MLX");
	if (errortype == 3)
		ft_putendl("Failed to initialize MLX window");
	if (p && p->fdf_window && p->fdf_window->window)
		mlx_destroy_window(p->mlx, p->fdf_window->window);
	if (p && p->mlx)
		free(p->mlx);
	exit(errortype);
	return (0);
}

void	make_hooks(void *mlx, t_window *fdf_window, t_params *hook_params)
{
	mlx_loop_hook(mlx, loop, hook_params);
	mlx_do_key_autorepeaton(mlx);
	mlx_hook(fdf_window->window,
		KeyPress, KeyPressMask, key_pressed, hook_params);
	mlx_hook(fdf_window->window,
		ButtonPress, ButtonPressMask, mouse_pressed, hook_params);
	mlx_hook(fdf_window->window,
		ButtonRelease, ButtonReleaseMask, mouse_released, hook_params);
	mlx_hook(fdf_window->window,
		DestroyNotify, NoEventMask, exit_program, hook_params);
	mlx_hook(fdf_window->window,
		MotionNotify, PointerMotionMask, mouse_motion, hook_params);
}

void	start(t_params *params, int argc, char **argv)
{
	params->fdf_window->infos_back_img = fill_img(params,
		new_pt(params, 325, 225), rgba_to_int(219, 219, 219, 80));
	srand(time(NULL));
	make_cos_table(params);
	make_sin_table(params);
	params->fdf_window->lanorme = make_lanorme(params);
	if ((params->fdf_window->line = malloc(sizeof(t_line))) == NULL)
		exit_program(params, 1);
	init_tabs(params, argc, argv);
	if (params->fdf_window->tabs)
	{
		render_top_menu(params);
		if (params->fdf_window->tabs->selected_tab)
		{
			hide_tab(params, params->fdf_window->tabs->selected_tab);
			render_tab(params, params->fdf_window->tabs->selected_tab);
		}
	}
	make_hooks(params->mlx, params->fdf_window, params);
	mlx_loop(params->mlx);
}

int		main(int argc, char **argv)
{
	void		*mlx;
	t_window	*fdf_window;
	t_params	*hook_params;

	mlx = NULL;
	fdf_window = NULL;
	mlx = init_graphics(NULL);
	if (argc < 2)
	{
		ft_putendl("Argument missing when launching the program");
		exit_program(NULL, 0);
	}
	else
	{
		fdf_window = create_window_struct(NULL, 1600, 1000, "FdF - cababou");
		fdf_window->window = NULL;
		init_window(NULL, mlx, fdf_window);
		if ((hook_params = malloc(sizeof(t_params))) == NULL)
			exit_program(hook_params, 1);
		hook_params->next_indentifier = 6000;
		hook_params->mlx = mlx;
		hook_params->fdf_window = fdf_window;
		start(hook_params, argc, argv);
	}
	return (0);
}
