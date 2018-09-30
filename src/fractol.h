/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 01:24:17 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 15:21:58 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define ERR_MEMORY 1
# define ERR_NOT_ENOUGH_ARGS 100
# define ERR_MLX_INIT 101
# define ERR_MLX_INIT_WINDOW 102

# define FRACTAL_MANDELBROT 300
# define FRACTAL_JULIA 301
# define FRACTAL_SHIP 302

# define BLACK_COLOR 1315860

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <Tk/X11/X.h>
# include "../libft/libft.h"

typedef struct		s_fractal
{
	long double		c_r;
	long double		c_i;
	long double		z_r;
	long double		z_i;
	long double		tmp;
	long			i;
	int				k;
}					t_fractal;

typedef struct		s_window
{
	void			*mlx;
	void			*window;
	int				width;
	int				height;
	int				size;
	int				fractal_type;
	int				is_closed;
	int				*need_check;
	int				max_iteration;
	void			*img_screen;
	int				*img_pixels;
	int				img_bits_per_pixel;
	int				img_size_line;
	int				img_endian;
	int				mouse_enabled;
	double			mouse_p1;
	double			mouse_p2;
	int				*colors;
	long double		zoom_x;
	long double		zoom_y;
	long double		x1;
	long double		x2;
	long double		y1;
	long double		y2;
}					t_window;

typedef struct		s_params
{
	void			*mlx;
	t_lstcontainer	*windows;
	int				need_check;
}					t_params;

void				exit_program(int code);
void				show_arguments(void);
void				handle_error(int code, int close);

void				init_windows(t_params *p, int argc, char **argv);
int					close_window(t_window *w);

int					loop_program(t_params *p);
int					key_press(int key, t_window *w);
int					mouse_release(int button, int x, int y, t_window *w);
int					mouse_press(int button, int x, int y, t_window *w);
void				handle_arrows(t_window *w, int key);
int					mouse_motion(int x, int y, t_window *w);
void				handle_iterations(int key, t_window *w);

void				zoom_mouse(t_window *w, double x, double y);
void				unzoom_mouse(t_window *w, double x, double y);
void				zoom_center(t_window *w, int x, int y);

void				r_zoom_mouse(t_window *w, double x, double y);
void				r_unzoom_mouse(t_window *w, double x, double y);
void				r_zoom_center(t_window *w, double x, double y);

void				make_screen(t_window *w);
void				destroy_image(t_window *w);

int					calc_gradient(int color1, int color2, double stage);
void				generate_colors(t_window *w);

void				mandelbrot_init(t_window *w);
void				mandelbrot_render(t_window *w);

void				julia_init(t_window *w);
void				julia_render(t_window *w);

void				ship_init(t_window *w);
void				ship_render(t_window *w);

void				re_render(t_window *w);
void				render_iterations(t_window *w);

void				show_controls(void);
void				reset_view(t_window *w);

#endif
