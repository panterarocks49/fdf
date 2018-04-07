/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:46:07 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/05 10:33:47 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# define WIN_X 800
# define WIN_Y 600
# define PADDING 120
# define PI 3.14159265
# define TORAD (PI / 180)

typedef struct	s_vert
{
	float	x;
	float	y;
	float	z;
}				t_vert;

typedef struct	s_map
{
	int		width;
	int		height;
	float	top_z;
	float	bot_z;
	t_list	*rows;
	t_list	*new_rows;
}				t_map;

typedef struct	s_image
{
	void	*mlx_img;
	char	*img_ptr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_image;

typedef struct	s_env
{
	void	*mlx;
	void	*window;
	t_map	*map;
	t_image	*img;
	int		win_x;
	int		win_y;
	float	init_scale;
	float	x_rot;
	float	y_rot;
	float	z_rot;
	float	x_shift;
	float	y_shift;
	float	z_shift;
	float	x_scale;
	float	y_scale;
	float	z_scale;
	int		color_scheme;
	int		color1;
	int		color2;
	int		color3;
	int		color4;
}				t_env;

void			usage_msg(void);
void			error_msg(void);
void			map_error_msg(void);

void			read_file(t_env *env, char *file);

void			image_pixel_put(t_env *env, float x, float y, int color);
t_image			*image_init(t_env *env);

void			set_vert(t_vert *vert, float x, float y, float z);

t_map			*map_init(int width);
void			center_map(t_map *map);

void			change_color_scheme(t_env *env);
int				line_color(t_env *env, t_vert *vert1, t_vert *vert2);

void			render(t_env *env);

void			mat_copy(float source[4][4], float dest[4][4]);
void			mat_mult_vec(t_vert *source, float mat[4][4], t_vert *dest);
void			mat_mult(float mat1[4][4], float mat2[4][4], float dest[4][4]);
void			init_mat_ident(float mat[4][4]);

void			mat_translate(float mat[4][4], float tx, float ty, float tz);
void			mat_scale(float mat[4][4], float sx, float sy, float sz);
void			mat_rotate(float mat[4][4], float ax, float ay, float az);

int				on_key_press(int key, t_env *env);
int				on_key_up(int key, t_env *env);
void			scale_all(float scale, t_env *env);

#endif
