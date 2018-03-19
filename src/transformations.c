/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:16:35 by jbrown            #+#    #+#             */
/*   Updated: 2018/03/16 18:16:36 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mat_translate(float mat[4][4], float tx, float ty, float tz)
{
	float	trmat[4][4];
	float	dest[4][4];

	init_mat_ident(trmat);
	trmat[3][0] = tx;
	trmat[3][1] = ty;
	trmat[3][2] = tz;
	mat_mult(mat, trmat, dest);
	mat_copy(dest, mat);
}

void	mat_scale(float mat[4][4], float sx, float sy, float sz)
{
	float	smat[4][4];
	float	dest[4][4];

	init_mat_ident(smat);
	smat[0][0] = sx;
	smat[1][1] = sy;
	smat[2][2] = sz;
	mat_mult(mat, smat, dest);
	mat_copy(dest, mat);
}

void	mat_rotate(float mat[4][4], float ax, float ay, float az)
{
	float	xmat[4][4];
	float	ymat[4][4];
	float	zmat[4][4];
	float	mat1[4][4];
	float	mat2[4][4];

	init_mat_ident(xmat);
	xmat[1][1] = cos(ax);
	xmat[1][2] = sin(ax);
	xmat[2][1] = -sin(ax);
	xmat[2][2] = cos(ax);
	init_mat_ident(ymat);
	ymat[0][0] = cos(ay);
	ymat[0][2] = -sin(ay);
	ymat[2][0] = sin(ay);
	ymat[2][2] = cos(ay);
	init_mat_ident(zmat);
	zmat[0][0] = cos(az);
	zmat[0][1] = sin(az);
	zmat[1][0] = -sin(az);
	zmat[1][1] = cos(az);
	mat_mult(mat, ymat, mat1);
	mat_mult(mat1, xmat, mat2);
	mat_mult(mat2, zmat, mat);
}
