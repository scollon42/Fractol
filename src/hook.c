/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:10:09 by scollon           #+#    #+#             */
/*   Updated: 2016/05/16 10:45:26 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		expose_hook(t_env *e)
{
	mlx_destroy_image(e->mlx, e->img.adr);
	init_img(e);
	fractal(e);
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img.adr, 0, 0);
	return (1);
}

int		move(t_env *e)
{
	if (e->mouse.zp || e->mouse.zm)
	{
		e->f.offx += (e->mouse.x - e->hw.x) / (e->hw.x) / e->f.zoom / 10;
		e->f.offy += (e->mouse.y - e->hw.y) / (e->hw.y) / e->f.zoom / 10;
		e->mouse.zp = 0;
		e->mouse.zm = 0;
	}
	if (e->fractal == 2 && !e->block)
	{
		e->f.cr = (e->mouse.x - e->hw.x) / 300.0f;
		e->f.ci = (e->mouse.y - e->hw.y) / 300.0f;
	}
	expose_hook(e);
	return (1);
}
