/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 11:12:18 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/30 18:26:01 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

double		calc_wall_distance(t_player *player, int side, t_raycaster ray)
{
	if (side == 0)
		return ((ray.map_pos.y - player->pos.y
		+ (1 - ray.step.y) / 2) / ray.dir.y);
	else
		return ((ray.map_pos.x - player->pos.x
		+ (1 - ray.step.x) / 2) / ray.dir.x);
}

/*
** Calculate the vector for the current ray on the plane
** x_view maps x from -1 to 1
*/

t_dpoint	set_raydir(int x, t_player *player)
{
	double		x_view;
	t_dpoint	ray_dir;

	x_view = 2 * (double)x / WIDTH - 1;
	ray_dir.x = player->looking_dir.x + player->plane.x * x_view;
	ray_dir.y = player->looking_dir.y + player->plane.y * x_view;
	return (ray_dir);
}

/*
** Calculate the draw height of the wall
*/

void		set_wall_height(int *draw_start, int *draw_end, int line_height)
{
	*draw_start = (-line_height / 2 + HEIGHT / 2);
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (line_height / 2 + HEIGHT / 2);
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

/*
** Calculate the side distanceof each step and init the step_dir to take
*/

t_point		calc_step_dir(t_player *player, t_raycaster ray,
t_dpoint *side_dist)
{
	t_point step;

	if (ray.dir.x < 0)
	{
		step.x = -1;
		side_dist->x = (player->pos.x - ray.map_pos.x) * ray.delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist->x = (ray.map_pos.x + 1.0 - player->pos.x) * ray.delta_dist.x;
	}
	if (ray.dir.y < 0)
	{
		step.y = -1;
		side_dist->y = (player->pos.y - ray.map_pos.y) * ray.delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist->y = (ray.map_pos.y + 1.0 - player->pos.y) * ray.delta_dist.y;
	}
	return (step);
}

/*
** Checks which side of the wall was hit
*/

int			wall_hit(int **map, t_raycaster ray, t_point *map_pos)
{
	int hit;
	int side;

	hit = 0;
	while (!hit)
	{
		if (ray.side_dist.y < ray.side_dist.x)
		{
			ray.side_dist.y += ray.delta_dist.y;
			map_pos->y += ray.step.y;
			side = 0;
		}
		else
		{
			ray.side_dist.x += ray.delta_dist.x;
			map_pos->x += ray.step.x;
			side = 1;
		}
		if (map[map_pos->y][map_pos->x] > 0
		&& map[map_pos->y][map_pos->x] <= WALLCOUNT)
			hit = 1;
	}
	return (side);
}
