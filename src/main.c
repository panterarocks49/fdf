/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:45:52 by jbrown            #+#    #+#             */
/*   Updated: 2018/03/10 18:59:26 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	env_init(t_env *env)
{
	env->mlx = NULL;
	env->window = NULL;
	env->img = NULL;
	env->win_x = WIN_X;
	env->win_y = WIN_Y;
	env->x_rot = 3;
	env->y_rot = -3;
	env->z_rot = 0;
	env->x_shift = 0;
	env->y_shift = 0;
	env->z_shift = 0;
	env->init_scale = 1;
	env->x_scale = 0;
	env->y_scale = 0;
	env->z_scale = 0;
	env->color_scheme = 0;
	env->color1 = 0xffffff;
	env->color2 = 0xffffff;
	env->color3 = 0xffffff;
	env->color4 = 0xffffff;
}

static void	print_ctrls(char *file)
{
	ft_putstr("-------DISPLAYING ");
	ft_putstr(file);
	ft_putendl("-------");
	ft_putendl("");
	ft_putendl("           42 FDF Controls");
	ft_putendl("     Arrow Keys:  Translate x/y Axes");
	ft_putendl("     A and D:     Rotate y Axis");
	ft_putendl("     W and S:     Rotate x Axis");
	ft_putendl("     Q and E:     Rotate z Axis");
	ft_putendl("     + and -:     Zoom in and out");
	ft_putendl("     c:           Change Color");
	ft_putendl("     Esc:         Quit");
	ft_putendl("");
}

static void	set_window_size(t_env *e)
{
	float padding;

	padding = PADDING;
	e->init_scale = FT_MIN((e->win_x - padding) / e->map->width,
							(e->win_y - padding) / e->map->height);
	while (e->init_scale < 10 && e->win_x <= 1200)
	{
		e->win_x += 100;
		e->win_y += 100;
		padding += 40;
		e->init_scale = FT_MIN((e->win_x - padding) / e->map->width,
								(e->win_y - padding) / e->map->height);
	}
}

int			main(int ac, char *av[])
{
	t_env	env;

	if (ac != 2)
		usage_msg();
	env_init(&env);
	read_file(&env, av[1]);
	set_window_size(&env);
	scale_all(env.init_scale, &env);
	env.mlx = mlx_init();
	env.window = mlx_new_window(env.mlx, env.win_x, env.win_y, "fdf");
	env.img = image_init(&env);
	render(&env);
	mlx_key_hook(env.window, on_key_up, &env);
	mlx_hook(env.window, 2, 0, on_key_press, &env);
	print_ctrls(av[1]);
	mlx_loop(env.mlx);
	return (0);
}
