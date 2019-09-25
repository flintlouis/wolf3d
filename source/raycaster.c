/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:51 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/25 11:12:39 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void			*raycaster(void *data)
{
	int draw_start;
	int draw_end;
	int side;
	int wall_height;

	double wall_distance;

	t_dpoint side_dist;
	t_dpoint delta_dist;
	t_dpoint ray_dir;

	t_point step;
	t_point map_pos;

	t_mlx *mlx;
	
	mlx = (t_mlx*)data;
	/* PLANE */
	while (mlx->x[0] < mlx->x[1])
	{
		/* CALC VECTOR FOR RAY ON PLANE POS */
		ray_dir = set_raydir(mlx->x[0], PLAYER);

		/* WHICH BOX THE PLAYER IS STANDING IN */
		map_pos = (t_point){(int)PLAYER->pos.x, (int)PLAYER->pos.y};

		/* DISTANCE FROM X/Y SIDE TO OTHER X/Y SIDE */
		delta_dist = (t_dpoint){fabs(1 / ray_dir.x), fabs(1 / ray_dir.y)};

		/* CALC STEP FOR MAP + INIT SIDE_DIST */
		step = calc_step_dir(PLAYER, ray_dir, &side_dist, delta_dist, map_pos);

		/* X OR Y WALL HIT */
		side = wall_hit(MAP, side_dist, delta_dist, &map_pos, step);

		wall_distance = calc_wall_distance(PLAYER, side, map_pos, step, ray_dir);

		mlx->z[mlx->x[0]] = wall_distance; ////////////////////////// Z buffer
		
		/* MULTIPLY HEIGHT FOR BIGGER WALLS */
		wall_height = (int)((/* 2 * */ HEIGHT) / wall_distance);

		/* SET HEIGHT OF WALLS TOO DRAW */
		set_wall_height(&draw_start, &draw_end, wall_height);

		////////////////////////////////////////////////////////////////////////////////////////////////////////// DRAW TEXTURES
		int texture_id;
		double wall_coll; /* Where exactly the wall was hit */
		int texture_x;

		texture_id = MAP[map_pos.y][map_pos.x] - 1;
		if (side == 0)
			wall_coll = PLAYER->pos.x + wall_distance * ray_dir.x;
		else
			wall_coll = PLAYER->pos.y + wall_distance * ray_dir.y;
		wall_coll -= floor(wall_coll);

		texture_x = (int)(wall_coll * TEXTURES[texture_id].width);
		if ((side == 0 && ray_dir.y > 0) || (side == 1 && ray_dir.x < 0))
			texture_x = TEXTURES[texture_id].width - texture_x - 1;
		
		draw_object(mlx, &TEXTURES[texture_id], mlx->x[0], (t_draw){wall_height, draw_start, draw_end, texture_x, side});
		mlx->x[0]++;
	}
	return (0);
}
