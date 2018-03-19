/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:54:38 by jbrown            #+#    #+#             */
/*   Updated: 2018/03/16 14:54:40 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mat_copy(float source[4][4], float dest[4][4])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			dest[i][j] = source[i][j];
	}
}

void	mat_mult_vec(t_vert *source, float mat[4][4], t_vert *dest)
{
	dest->x = source->x * mat[0][0] + source->y * mat[1][0]
			+ source->z * mat[2][0] + mat[3][0];
	dest->y = source->x * mat[0][1] + source->y * mat[1][1]
			+ source->z * mat[2][1] + mat[3][1];
	dest->z = source->x * mat[0][2] + source->y * mat[1][2]
			+ source->z * mat[2][2] + mat[3][2];
}

void	mat_mult(float mat1[4][4], float mat2[4][4], float dest[4][4])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			dest[i][j] = mat1[i][0] * mat2[0][j]
						+ mat1[i][1] * mat2[1][j]
						+ mat1[i][2] * mat2[2][j]
						+ mat1[i][3] * mat2[3][j];
	}
}

void	init_mat_ident(float mat[4][4])
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
			j++;
		}
		i++;
	}
}
