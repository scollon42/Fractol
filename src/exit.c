/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 15:43:07 by scollon           #+#    #+#             */
/*   Updated: 2016/01/14 08:36:06 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		clean(t_env *e)
{
	e->img.adr != NULL ? mlx_destroy_image(e->mlx, e->img.adr) : 0;
	e->win != NULL ? mlx_destroy_window(e->mlx, e->win) : 0;
	free(e->mlx);
	ft_strdel(&e->arg.fractal);
	ft_memdel((void**)&e->f.color);
	free(e);
	exit(0);
}

void		error(t_env *e, char *type)
{
	if (type != NULL)
		ft_putstr_fd(type, 2);
	clean(e);
}
