/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 10:46:08 by scollon           #+#    #+#             */
/*   Updated: 2016/03/30 10:12:51 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	*init_color(t_env *e)
{
	int		*color;

	if (!(color = (int *)malloc(sizeof(int) * 9)))
		error(e, "Error : Colors set init failed\n");
	color[0] = 0x280004;
	color[1] = 0x002804;
	color[2] = 0x040028;
	color[3] = 0x282828;
	color[4] = 0x000928;
	color[5] = 0x500505;
	color[6] = 0xFF2800;
	color[7] = 0x00FF28;
	color[8] = 0x2800FF;
	return (color);
}

static void	init_f(t_env *e)
{
	e->f.x = 0;
	e->f.y = 0;
	e->f.offx = 0.0;
	e->f.offy = 0.0;
	e->f.cr = 0.0;
	e->f.ci = 0.0;
	e->f.color = init_color(e);
	e->f.cc = 0;
	e->f.zoom = 0.25f;
}

static void	init_k(t_env *e)
{
	e->key.ku = 0;
	e->key.kd = 0;
	e->key.kl = 0;
	e->key.kr = 0;
}

void		init_img(t_env *e)
{
	if (!(e->img.adr = mlx_new_image(e->mlx, e->w.x, e->w.y)))
		error(e, "Error : Failed to init image\n");
	e->img.img = mlx_get_data_addr(e->img.adr,
			&e->img.bpp, &e->img.sl, &e->img.endian);
	e->img.opp = e->img.bpp / 8;
}

void		init_env(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		error(e, "Error : Mlx init failed\n");
	e->w.x = e->arg.wd;
	e->w.y = e->arg.hg;
	if (!(e->win = mlx_new_window(e->mlx, e->w.x, e->w.y, e->arg.fractal)))
		error(e, "Error : Window init failed\n");
	e->hw.x = e->w.x / 2;
	e->hw.y = e->w.y / 2;
	e->max = 30;
	e->pix = 1;
	e->mouse.x = e->hw.x;
	e->mouse.y = e->hw.y;
	e->mouse.zp = 0;
	e->mouse.zm = 0;
	e->move.x = 0;
	e->move.y = 0;
	e->block = 0;
	init_f(e);
	init_img(e);
}
