/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_enemy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:39 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/26 17:43:04 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

static double	distance(t_dpoint a, t_dpoint b)
{
	double d;
	double dx;
	double dy;

	dx = (double)b.x - a.x;
	dy = (double)b.y - a.y;
	d = sqrt(((dx * dx) + (dy * dy)));
	return (d);
}

static	void	free_grid(t_node **grid, t_point grid_size, t_enemy *enemy)
{
	int i;
	int j;

	i = 0;
	while (i < grid_size.x)
	{
		j = 0;
		while (j < grid_size.y)
		{
			grid[i][j].next = NULL;
			grid[i][j].prev = NULL;
			grid[i][j].f = 0;
			grid[i][j].g = 0;
			grid[i][j].h = 0;
			j++;
		}
		i++;
	}
	enemy->start = NULL;
	enemy->end = NULL;
	enemy->open_set = NULL;
	enemy->closed_set = NULL;
	enemy->path = NULL;
}

static	void	enemy_pathfinding(t_mlx *mlx, double *x, double *y, int i)
{
	ENEMIES[i].start =
	&mlx->grid[(int)(PLAYER->pos.x - 1)][(int)(PLAYER->pos.y - 1)];
	ENEMIES[i].end = &mlx->grid[(int)(ENEMIES[i].ss->location.x - 1)]
	[(int)(ENEMIES[i].ss->location.y - 1)];
	ENEMIES[i].open_set = ENEMIES[i].start;
	while (ENEMIES[i].open_set
	&& !compare_nodes(ENEMIES[i].path, ENEMIES[i].end))
		find_path(&ENEMIES[i].open_set, &ENEMIES[i].closed_set,
		&ENEMIES[i].path, ENEMIES[i].end);
	*x = ENEMIES[i].ss->location.x + (((ENEMIES[i].path->prev->loc.x
	+ 1.5) - ENEMIES[i].ss->location.x) / 10);
	*y = ENEMIES[i].ss->location.y + (((ENEMIES[i].path->prev->loc.y
	+ 1.5) - ENEMIES[i].ss->location.y) / 10);
}

void			move_enemy(t_mlx *mlx)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	while (i < LEVEL->enemy_count)
	{
		if (!ENEMIES[i].ss->hit)
		{
			enemy_pathfinding(mlx, &x, &y, i);
			ENEMIES[i].ss->sprite = TEXTURES[ENEMY - 1];
			if (distance(ENEMIES[i].ss->location, PLAYER->pos) >= 7.5)
				ENEMIES[i].ss->location = (t_dpoint){x, y};
			else
			{
				ENEMIES[i].shoot = !ENEMIES[i].shoot ? 1 : 0;
				ENEMIES[i].ss->sprite = TEXTURES[ENEMIES[i].shoot + 19];
				if (mlx->z[WIDTH >> 1] > ENEMIES[i].ss->rel_loc.y)
					PLAYER->health -= PLAYER->health > 0 ? 2 : 0;
			}
			free_grid(mlx->grid, (t_point){(LEVEL->size.x - 2),
			(LEVEL->size.y - 2)}, &ENEMIES[i]);
		}
		i++;
	}
}
