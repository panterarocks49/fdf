/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 12:45:26 by jbrown            #+#    #+#             */
/*   Updated: 2018/03/18 12:45:28 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_color_scheme(t_env *env)
{
	env->color1 = rand();
	env->color2 = rand();
	env->color3 = rand();
	env->color4 = rand();
	if (env->color_scheme == 0)
	{
		env->color1 = 0xffffff;
		env->color2 = 0xffffff;
		env->color3 = 0xffffff;
		env->color4 = 0xffffff;
	}
	else if (env->color_scheme == 1)
	{
		env->color1 = 0xffffff;
		env->color2 = 0x42e5f4;
		env->color3 = 0x21f25c;
		env->color4 = 0xf0381f;
	}
	else if (env->color_scheme == 2)
	{
		env->color1 = 0x007c04;
		env->color2 = 0x591d1d;
		env->color3 = 0x35b2ce;
		env->color4 = 0xffffff;
	}
}

void		change_color_scheme(t_env *env)
{
	if (env->color_scheme + 1 < 4)
		env->color_scheme++;
	else
		env->color_scheme = 0;
	set_color_scheme(env);
}

int			line_color(t_env *env, t_vert *vert1, t_vert *vert2)
{
	float min;
	float z_diff;
	float diff;

	min = FT_MIN(vert1->z, vert2->z);
	z_diff = FT_ABS(vert1->z - vert2->z);
	diff = env->map->top_z - env->map->bot_z;
	if (min + z_diff / 2 <= env->map->bot_z + (diff / 4))
		return (env->color1);
	else if (min + z_diff / 2 <= env->map->bot_z + (2 * diff / 3))
		return (env->color2);
	else if (min + z_diff / 2 <= env->map->bot_z + (3 * diff / 4))
		return (env->color3);
	else
		return (env->color4);
}
