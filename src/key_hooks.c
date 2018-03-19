/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 22:09:31 by jbrown            #+#    #+#             */
/*   Updated: 2018/03/15 22:09:33 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translation_hook(int key, t_env *env)
{
	if (key == 123)
		env->x_shift -= 10;
	else if (key == 124)
		env->x_shift += 10;
	else if (key == 125)
		env->y_shift += 10;
	else if (key == 126)
		env->y_shift -= 10;
}

void		scale_all(float scale, t_env *env)
{
	if (env->x_scale + scale >= 1.5)
		env->x_scale += scale;
	if (env->y_scale + scale >= 1.5)
		env->y_scale += scale;
	if (env->z_scale + scale >= 1.5)
		env->z_scale += scale;
}

int			on_key_press(int key, t_env *env)
{
	if (key >= 123 && key <= 126)
		translation_hook(key, env);
	else if (key == 12)
		env->z_rot += 1;
	else if (key == 14)
		env->z_rot -= 1;
	else if (key == 13)
		env->x_rot += 1;
	else if (key == 1)
		env->x_rot -= 1;
	else if (key == 0)
		env->y_rot -= 1;
	else if (key == 2)
		env->y_rot += 1;
	if (key == 69)
		scale_all(0.5, env);
	if (key == 78)
		scale_all(-0.5, env);
	render(env);
	return (0);
}

int			on_key_up(int key, t_env *env)
{
	if (key == 53)
		exit(0);
	else if (key == 8)
		change_color_scheme(env);
	render(env);
	return (0);
}
