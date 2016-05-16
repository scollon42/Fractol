/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 09:44:07 by scollon           #+#    #+#             */
/*   Updated: 2016/03/31 08:49:17 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct		s_arg
{
	char			*fractal;
	int				wd;
	int				hg;
}					t_arg;

typedef	struct		s_img
{
	void			*adr;
	char			*img;
	int				endian;
	int				bpp;
	int				sl;
	int				opp;
}					t_img;

typedef struct		s_rect
{
	double			x;
	double			y;
}					t_rect;

typedef	struct		s_key
{
	int				ku;
	int				kd;
	int				kl;
	int				kr;
}					t_key;

typedef	struct		s_mouse
{
	int				x;
	int				y;
	int				zp;
	int				zm;
}					t_mouse;

typedef	struct		s_fra
{
	int				*color;
	int				cc;
	double			cr;
	double			ci;
	double			x;
	double			y;
	double			x2;
	double			y2;
	double			zoom;
	double			offx;
	double			offy;
	t_rect			zw;

}					t_fra;

typedef	struct		s_env
{
	char			block;
	void			*mlx;
	void			*win;
	int				max;
	int				fractal;
	int				pix;
	t_arg			arg;
	t_img			img;
	t_rect			w;
	t_rect			hw;
	t_rect			move;
	t_fra			f;
	t_key			key;
	t_mouse			mouse;
}					t_env;

/*
**			Env initialisation functions
*/
void				init_env(t_env *e);
void				init_img(t_env *e);

/*
**			Event handles functions
*/
int					move(t_env *e);
int					expose_hook(t_env *e);
int					mouse_pos(int x, int y, t_env *e);
int					mouse_event(int btn, int x, int y, t_env *e);
int					key_press(int kc, t_env *env);
int					key_release(int kc, t_env *env);

/*
**			Draw fractals functions
*/
void				fractal(t_env *e);
void				img_pixel_put(t_env *env, int x, int y, int color);

/*
**			Functions used to quit with style
*/
void				clean(t_env *e);
void				error(t_env *e, char *type);

#endif
