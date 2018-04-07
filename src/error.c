/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 19:40:01 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/05 10:52:06 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	usage_msg(void)
{
	ft_putendl_fd("usage: ./fdf [target_file.fdf]", 2);
	exit(0);
}

void	error_msg(void)
{
	perror("error");
	exit(1);
}

void	map_error_msg(void)
{
	ft_putendl_fd("error: invalid map", 2);
	exit(0);
}
