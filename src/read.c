/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:37:22 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/05 10:50:19 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*read_line(t_env *env, char *str, int width, int y)
{
	int		x;
	t_vert	*verts;
	t_list	*lst;

	if (ft_countwords(str, ' ') != width)
		map_error_msg();
	x = 0;
	verts = (t_vert *)malloc(sizeof(t_vert) * width);
	while (*str)
	{
		set_vert((verts + x), x, y, ft_atoi(str));
		env->map->top_z = FT_MAX(env->map->top_z, (verts + x)->z);
		env->map->bot_z = FT_MIN(env->map->bot_z, (verts + x)->z);
		while (*str && *str != ' ')
			str++;
		while (*str && *str == ' ')
			str++;
		x++;
	}
	lst = ft_lstnew((void *)verts, (sizeof(t_vert) * width));
	free(verts);
	return (lst);
}

static void		finish_read(t_env *e, int fd)
{
	if (close(fd) == -1)
		error_msg();
	center_map(e->map);
	e->map->new_rows = ft_lstdup(e->map->rows);
}

void			read_file(t_env *e, char *file)
{
	int		fd;
	char	*str;
	t_list	*row;

	if ((fd = open(file, O_RDONLY)) < 0)
		error_msg();
	if (get_next_line(fd, &str) == 1)
	{
		e->map = map_init(ft_countwords(str, ' '));
		e->map->rows = read_line(e, str, e->map->width, e->map->height++);
		row = e->map->rows;
		free(str);
		while (get_next_line(fd, &str) == 1)
		{
			row->next = read_line(e, str, e->map->width, e->map->height++);
			row = row->next;
			free(str);
		}
	}
	else
		error_msg();
	free(str);
	finish_read(e, fd);
}
