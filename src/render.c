/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:06:03 by jbrown            #+#    #+#             */
/*   Updated: 2018/03/16 14:06:04 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_dy_dx(int *dy, int *dx, t_vert *vert1, t_vert *vert2)
{
	int temp;

	*dy = FT_ABS(vert2->y - vert1->y);
	*dx = FT_ABS(vert2->x - vert1->x);
	if (*dy > *dx)
	{
		temp = *dy;
		*dy = *dx;
		*dx = temp;
	}
}

static void	draw_line(t_env *env, t_vert *vert1, t_vert *vert2, int color)
{
	int		dx;
	int		dy;
	int		p;
	t_vert	vert_counter;

	set_vert(&vert_counter, (int)vert1->x, (int)vert1->y, 0);
	set_dy_dx(&dy, &dx, vert1, vert2);
	p = 2 * dy - dx;
	while (vert_counter.z++ < dx + 1)
	{
		image_pixel_put(env, vert_counter.x, vert_counter.y, color);
		while (p >= 0)
		{
			p -= 2 * (dx + 1);
			if (FT_ABS(vert2->y - vert1->y) > FT_ABS(vert2->x - vert1->x))
				vert_counter.x += FT_SIGN(vert2->x - vert1->x);
			else
				vert_counter.y += FT_SIGN(vert2->y - vert1->y);
		}
		p += 2 * dy;
		if (FT_ABS(vert2->y - vert1->y) > FT_ABS(vert2->x - vert1->x))
			vert_counter.y += FT_SIGN(vert2->y - vert1->y);
		else
			vert_counter.x += FT_SIGN(vert2->x - vert1->x);
	}
}

static void	transform(t_env *e)
{
	float	mat[4][4];
	t_list	*r;
	t_list	*n_r;
	int		x;

	r = e->map->rows;
	n_r = e->map->new_rows;
	init_mat_ident(mat);
	mat_scale(mat, e->x_scale, e->y_scale, e->z_scale);
	mat_rotate(mat, e->x_rot * TORAD, e->y_rot * TORAD, e->z_rot * TORAD);
	mat_translate(mat, e->x_shift + ((e->win_x - e->map->width * e->init_scale)
	+ e->map->width * e->init_scale) / 2, e->y_shift +
	((e->win_y - e->map->height * e->init_scale)
	+ e->map->height * e->init_scale) / 2, e->z_shift);
	while (r && n_r && (x = -1) == -1)
	{
		while (++x < e->map->width)
		{
			mat_mult_vec((t_vert *)r->content + x,
				mat, (t_vert *)n_r->content + x);
		}
		r = r->next;
		n_r = n_r->next;
	}
}

void		render(t_env *e)
{
	int		x;
	t_list	*n_r;
	t_list	*r;

	ft_bzero(e->img->img_ptr, (e->win_x * e->win_y * e->img->bpp));
	transform(e);
	n_r = e->map->new_rows;
	r = e->map->rows;
	while (n_r && r && (x = -1) == -1)
	{
		while (++x < e->map->width)
		{
			if (n_r->next)
				draw_line(e, (t_vert *)n_r->content + x,
(t_vert *)n_r->next->content + x,
line_color(e, (t_vert *)r->content + x, (t_vert *)r->next->content + x));
			if (x < e->map->width - 1)
				draw_line(e, (t_vert *)n_r->content + x,
(t_vert *)n_r->content + x + 1,
line_color(e, (t_vert *)r->content + x, (t_vert *)r->content + x + 1));
		}
		n_r = n_r->next;
		r = r->next;
	}
	mlx_put_image_to_window(e->mlx, e->window, e->img->mlx_img, 0, 0);
}
