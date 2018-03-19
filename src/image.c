/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:11:15 by jbrown            #+#    #+#             */
/*   Updated: 2018/03/12 13:11:17 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	image_pixel_put(t_env *env, float x, float y, int color)
{
	t_image	*img;

	img = env->img;
	if (x >= 0 && y >= 0 && x < env->win_x && y < env->win_y)
		*(int *)(img->img_ptr + (int)((y * env->win_x) + x) * img->bpp) = color;
}

t_image	*image_init(t_env *env)
{
	t_image	*img;

	if (!(img = (t_image *)malloc(sizeof(t_image))))
		return (NULL);
	img->mlx_img = mlx_new_image(env->mlx, env->win_x, env->win_y);
	img->img_ptr = mlx_get_data_addr(img->mlx_img, &img->bpp,
		&img->size_line, &img->endian);
	img->bpp /= 8;
	return (img);
}
