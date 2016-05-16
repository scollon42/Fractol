/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:26:54 by scollon           #+#    #+#             */
/*   Updated: 2016/05/16 10:45:55 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	color(t_env *e, int i)
{
	int	color;

	color = e->f.color[e->f.cc];
	if (i < 3)
		return (color);
	return ((color >> 1) * i);
}

static void	burningship(t_env *e, int x, int y)
{
	int		i;

	i = 0;
	e->f.x = 0;
	e->f.y = 0;
	e->f.x2 = 0;
	e->f.y2 = 0;
	e->f.cr = (x - e->hw.x) / e->f.zw.x + e->f.offx;
	e->f.ci = (y - e->hw.y) / e->f.zw.y + e->f.offy;
	while (e->f.x2 + e->f.y2 < 4 && i < e->max)
	{
		e->f.y = 2.0 * fabs(e->f.x * e->f.y) + e->f.ci;
		e->f.x = e->f.x2 - e->f.y2 - e->f.cr;
		e->f.x2 = (e->f.x * e->f.x);
		e->f.y2 = (e->f.y * e->f.y);
		++i;
	}
	if (i == e->max)
		img_pixel_put(e, x, y, 0);
	else
		img_pixel_put(e, x, y, color(e, i));
}

static void	mandelbrot(t_env *e, int x, int y)
{
	int		i;

	i = 0;
	e->f.x = 0;
	e->f.y = 0;
	e->f.x2 = 0;
	e->f.y2 = 0;
	e->f.cr = (x - e->hw.x) / e->f.zw.x + e->f.offx + e->move.x;
	e->f.ci = (y - e->hw.y) / e->f.zw.y + e->f.offy + e->move.y;
	while (e->f.x2 + e->f.y2 < 4 && i < e->max)
	{
		e->f.y = 2.0 * e->f.x * e->f.y + e->f.ci;
		e->f.x = e->f.x2 - e->f.y2 + e->f.cr;
		e->f.x2 = e->f.x * e->f.x;
		e->f.y2 = e->f.y * e->f.y;
		++i;
	}
	if (i == e->max)
		img_pixel_put(e, x, y, 0);
	else
		img_pixel_put(e, x, y, color(e, i));
}

static void	julia(t_env *e, int x, int y)
{
	int		i;

	i = 0;
	e->f.x = (x - e->hw.x) / e->f.zw.x + e->f.offx;
	e->f.y = (y - e->hw.y) / e->f.zw.y + e->f.offy;
	e->f.x2 = e->f.x * e->f.x;
	e->f.y2 = e->f.y * e->f.y;
	while (e->f.x2 + e->f.y2 < 4 && i < e->max)
	{
		e->f.y = 2.0 * e->f.x * e->f.y + e->f.ci;
		e->f.x = e->f.x2 - e->f.y2 + e->f.cr;
		e->f.x2 = e->f.x * e->f.x;
		e->f.y2 = e->f.y * e->f.y;
		++i;
	}
	if (i == e->max)
		img_pixel_put(e, x, y, 0);
	else
		img_pixel_put(e, x, y, color(e, i));
}

void		fractal(t_env *e)
{
	int x;
	int	y;

	y = 0;
	e->f.zw.x = e->f.zoom * e->w.x;
	e->f.zw.y = e->f.zoom * e->w.y;
	while (y < e->w.y)
	{
		x = 0;
		while (x < e->w.x)
		{
			e->fractal == 1 ? mandelbrot(e, x, y) : 0;
			e->fractal == 2 ? julia(e, x, y) : 0;
			e->fractal == 3 ? burningship(e, x, y) : 0;
			x += e->pix;
		}
		y += e->pix;
	}
}
