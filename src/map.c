/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 19:13:58 by jbrown            #+#    #+#             */
/*   Updated: 2018/03/16 19:14:01 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*map_init(int width)
{
	t_map *map;

	map = (t_map *)malloc(sizeof(t_map));
	map->width = width;
	map->height = 0;
	map->bot_z = 0;
	map->top_z = 0;
	map->rows = NULL;
	map->new_rows = NULL;
	return (map);
}

void	center_map(t_map *map)
{
	int		i;
	int		j;
	t_list	*rows;
	t_vert	*verts;

	i = 0;
	rows = map->rows;
	while (rows)
	{
		j = 0;
		verts = (t_vert *)rows->content;
		while (j < map->width)
		{
			verts[j].x = (j - map->width / 2);
			verts[j].y = (i - map->height / 2);
			j++;
		}
		i++;
		rows = rows->next;
	}
}
