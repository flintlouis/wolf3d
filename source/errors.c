/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/26 15:04:09 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/26 17:14:35 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdlib.h>

void	fd_error(int fd)
{
	if (fd < 0)
	{
		ft_putendl("ERROR : Not a valid file");
		exit(1);
	}
}

void	info_error(t_level *level, t_player *player)
{
	if (!level->size.x || !level->size.y
	|| !(int)player->pos.x || !(int)player->pos.y)
	{
		ft_putendl("ERROR : Incorrect level file");
		exit(1);
	}
	if (player->pos.x >= (level->size.x - 1)
	|| (player->pos.y >= level->size.y - 1))
	{
		ft_putendl("ERROR : Incorrect level file");
		exit(1);
	}
}

void	size_error1(int i, int j, t_point size)
{
	if (i > size.x || j > size.y)
	{
		ft_putendl("ERROR : Incorrect level size");
		exit(1);
	}
}

void	size_error2(int n, int size)
{
	if (n < size)
	{
		ft_putendl("ERROR : Incorrect level size");
		exit(1);
	}
}

void	spawn_error(int i, int j, t_dpoint spawn)
{
	if ((int)spawn.x == i && (int)spawn.y == j)
	{
		ft_putendl("ERROR : Misplaced spawn");
		exit(1);
	}
}
