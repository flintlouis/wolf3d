/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:51 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/25 15:49:11 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

static void		add_texture(t_mlx *mlx, t_raycaster ray,
double wall_distance, t_draw draw)
{
	int		texture_id;
	double	wall_coll;

	texture_id = MAP[ray.map_pos.y][ray.map_pos.x] - 1;
	if (draw.side == 0)
		wall_coll = PLAYER->pos.x + wall_distance * ray.dir.x;
	else
		wall_coll = PLAYER->pos.y + wall_distance * ray.dir.y;
	wall_coll -= floor(wall_coll);
	draw.x = (int)(wall_coll * TEXTURES[texture_id].width);
	if ((draw.side == 0 && ray.dir.y > 0) || (draw.side == 1 && ray.dir.x < 0))
		draw.x = TEXTURES[texture_id].width - draw.x - 1;
	draw_object(mlx, &TEXTURES[texture_id], mlx->x[0], draw);
}

/*
** Calculate the vector for the current ray on the plane
** Which loc is the player standing
** DISTANCE FROM X/Y SIDE TO OTHER X/Y SIDE
** CALC STEP FOR MAP + INIT SIDE_DIST
** X OR Y WALL HIT
** ADD DISTANCE TO Z BUFFER
** SET HEIGHT OF WALLS TOO DRAW
*/

void			*raycaster(void *data)
{
	double		wall_distance;
	t_raycaster	ray;
	t_draw		draw;
	t_mlx		*mlx;

	mlx = (t_mlx*)data;
	while (mlx->x[0] < mlx->x[1])
	{
		ray.dir = set_raydir(mlx->x[0], PLAYER);
		ray.map_pos = (t_point){(int)PLAYER->pos.x, (int)PLAYER->pos.y};
		ray.delta_dist = (t_dpoint){fabs(1 / ray.dir.x), fabs(1 / ray.dir.y)};
		ray.step = calc_step_dir(PLAYER, ray, &ray.side_dist);
		draw.side =
		wall_hit(MAP, ray, &ray.map_pos);
		wall_distance =
		calc_wall_distance(PLAYER, draw.side, ray);
		mlx->z[mlx->x[0]] = wall_distance;
		draw.height = (int)((HEIGHT) / wall_distance);
		set_wall_height(&draw.start, &draw.end, draw.height);
		add_texture(mlx, ray, wall_distance, draw);
		mlx->x[0]++;
	}
	return (0);
}
