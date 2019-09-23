/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:42 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/23 12:38:36 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		check_collision(t_mlx *mlx, int x, int y)
{
	int i;

	i = 0;
	if (MAP[y][x] > 0 && MAP[y][x] <= OBJECTCOL)
		return (1);
	while (i < LEVEL->enemy_count)
	{
		if (!ENEMIES[i].ss->hit &&
		(int)ENEMIES[i].ss->location.y == y
		&& (int)ENEMIES[i].ss->location.x == x)
			return (1);
		i++;
	}
	return (0);
}

static void		move(t_dpoint *move, t_mlx *mlx, double direction)
{
	double tmpy;
	double tmpx;

	if (CONTROLS->run)
		direction /= 6;
	else
		direction /= 11;
	tmpy = PLAYER->pos.y + (direction * move->y);
	tmpx = PLAYER->pos.x + (direction * move->x);
	if (!check_collision(mlx, PLAYER->pos.x, tmpy))
		PLAYER->pos.y = tmpy;
	if (!check_collision(mlx, tmpx, PLAYER->pos.y))
		PLAYER->pos.x = tmpx;
}

void			move_player(t_mlx *mlx)
{
	if (CONTROLS->front)
		move(&PLAYER->looking_dir, mlx, 1);
	if (CONTROLS->back)
		move(&PLAYER->looking_dir, mlx, -1);
	if (CONTROLS->left)
		move(&PLAYER->plane, mlx, -1);
	if (CONTROLS->right)
		move(&PLAYER->plane, mlx, 1);
}
