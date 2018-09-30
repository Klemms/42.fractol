/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 01:29:43 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 06:34:36 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_error(int code, int close)
{
	if (code == ERR_MEMORY)
		ft_putendl("Memory Error");
	if (code == ERR_MLX_INIT)
		ft_putendl("Couldn't initialize mlx");
	if (code == ERR_MLX_INIT_WINDOW)
		ft_putendl("Couldn't initialize mlx window");
	if (code == ERR_NOT_ENOUGH_ARGS)
	{
		ft_putendl("Not enough arguments");
		show_arguments();
	}
	if (close)
		exit_program(code);
}

void	show_arguments(void)
{
	ft_putendl("Usage : fractol <fractal name> [fractal name...]");
	ft_putendl("");
	ft_putendl("Available Fractals :");
	ft_putendl(" - mandelbrot");
	ft_putendl(" - julia");
	ft_putendl(" - ship");
}
