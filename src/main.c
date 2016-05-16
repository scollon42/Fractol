/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 09:46:47 by scollon           #+#    #+#             */
/*   Updated: 2016/01/14 08:46:26 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	aff_help(void)
{
	ft_putstr("\n\033[1;32mUsage :\033[0m \033[1m./fractol fractal_name");
	ft_putendl(" [-w window width] [-h window height]\033[0m");
	ft_putendl("\n\033[1mRequired fractal_name :\033[0m");
	ft_putendl("        - mandelbrot");
	ft_putendl("        - julia");
	ft_putendl("        - burningship");
	ft_putendl("\033[1mOptions :\033[0m");
	ft_putendl("        -w     : set windows width");
	ft_putendl("        -h     : set windows height");
	ft_putendl("        --help : print help");
	ft_putendl("\033[1mHow to use :\033[0m");
	ft_putendl("	Use arrow to move (only mandelbrot)");
	ft_putendl("	Use + / - to change iterations");
	ft_putendl("	Use f to swich fractals type");
	ft_putendl("	Use < - > to switch colors");
	ft_putendl("	Use P or O to swith to pixel or full mode");
	exit(0);
}

static void	read_arg(t_env *e, int ac, char **av)
{
	int i;

	i = 0;
	e->arg.wd = 0;
	e->arg.hg = 0;
	if (ft_strcmp(av[1], "mandelbrot") != 0 && ft_strcmp(av[1], "julia") != 0
			&& ft_strcmp(av[1], "burningship") != 0)
		aff_help();
	if (!(e->arg.fractal = ft_strdup(av[1])))
		clean(e);
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-w") == 0 && i + 1 < ac)
			e->arg.wd = ft_atoi(av[i + 1]);
		else if (ft_strcmp(av[i], "-h") == 0 && i + 1 < ac)
			e->arg.hg = ft_atoi(av[i + 1]);
		i++;
	}
	e->arg.wd = (e->arg.wd < 200 || e->arg.wd > 2000 ? 700 : e->arg.wd);
	e->arg.hg = (e->arg.hg < 200 || e->arg.hg > 2000 ? 700 : e->arg.hg);
	ft_strcmp(e->arg.fractal, "mandelbrot") == 0 ? e->fractal = 1 : 0;
	ft_strcmp(e->arg.fractal, "julia") == 0 ? e->fractal = 2 : 0;
	ft_strcmp(e->arg.fractal, "burningship") == 0 ? e->fractal = 3 : 0;
}

int			main(int ac, char **av)
{
	t_env *e;

	if (ac < 2 || ac > 6)
		aff_help();
	else
	{
		ft_strcmp(av[1], "--help") == 0 ? aff_help() : 0;
		if (!(e = (t_env*)malloc(sizeof(t_env))))
			return (0);
		read_arg(e, ac, av);
		init_env(e);
		mlx_mouse_hook(e->win, mouse_event, e);
		mlx_hook(e->win, 6, (1L << 6), mouse_pos, e);
		mlx_hook(e->win, 2, (1L << 0), key_press, e);
		mlx_hook(e->win, 3, (1L << 1), key_release, e);
		mlx_expose_hook(e->win, expose_hook, e);
		mlx_loop_hook(e->mlx, move, e);
		mlx_loop(e->mlx);
		clean(e);
	}
	return (0);
}
