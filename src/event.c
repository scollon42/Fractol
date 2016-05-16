/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 08:14:02 by scollon           #+#    #+#             */
/*   Updated: 2016/03/30 10:14:31 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_pos(int x, int y, t_env *e)
{
	e->mouse.x = x;
	e->mouse.y = y;
	return (1);
}

int		mouse_event(int btn, int x, int y, t_env *e)
{
	e->mouse.x = x;
	e->mouse.y = y;
	btn == 4 ? e->f.zoom *= 1.05f : 0;
	btn == 5 ? e->f.zoom *= 0.95f : 0;
	e->f.zoom < 0.01f ? e->f.zoom = 0.01f : 0;
	btn == 4 ? e->mouse.zp = 1 : 0;
	btn == 5 ? e->mouse.zm = 1 : 0;
	return (1);
}

void	key_switch(char *k)
{
	*k = *k == 1 ?  0 : 1;
}

int		key_press(int kc, t_env *e)
{
	kc == 53 ? clean(e) : 0;
	kc == 34 ? key_switch(&e->block) : 0;
	e->key.ku = (kc == 126 ? 1 : 0);
	e->key.kd = (kc == 125 ? 1 : 0);
	e->key.kl = (kc == 123 ? 1 : 0);
	e->key.kr = (kc == 124 ? 1 : 0);
	e->move.x += (e->key.kr - e->key.kl) * 0.05f / e->f.zoom;
	e->move.y += (e->key.kd - e->key.ku) * 0.05f / e->f.zoom;
	kc == 69 ? e->max += 1 : 0;
	kc == 78 ? e->max -= 1 : 0;
	e->max < 1 ? e->max = 1 : 0;
	kc == 43 ? e->f.cc -= 1 : 0;
	kc == 47 ? e->f.cc += 1 : 0;
	e->f.cc = (e->f.cc < 0 ? 8 : e->f.cc);
	e->f.cc = (e->f.cc > 8 ? 0 : e->f.cc);
	if (kc == 3)
	{
		e->fractal += 1;
		e->f.offx = 0.0f;
		e->f.offy = 0.0f;
		e->f.zoom = 0.25f;
		e->fractal = (e->fractal > 3 ? 1 : e->fractal);
	}
	e->pix = (kc == 35 && e->pix == 1 ? 5 : e->pix);
	e->pix = (kc == 31 && e->pix == 5 ? 1 : e->pix);
	return (1);
}

int		key_release(int kc, t_env *e)
{
	e->key.ku = (kc == 126 ? 0 : 0);
	e->key.kd = (kc == 125 ? 0 : 0);
	e->key.kl = (kc == 123 ? 0 : 0);
	e->key.kr = (kc == 124 ? 0 : 0);
	return (1);
}
