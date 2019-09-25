/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 11:12:18 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/25 11:13:07 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

double	calc_wall_distance(t_player *player, int side, t_point map_pos, t_point step, t_dpoint ray_dir)
{
	if (side == 0)
		return ((map_pos.y - player->pos.y + (1 - step.y) / 2) / ray_dir.y);
	else
		return ((map_pos.x - player->pos.x + (1 - step.x) / 2) / ray_dir.x);

}

t_dpoint	set_raydir(int x, t_player *player)
{
	double		x_view;
	t_dpoint	ray_dir;

	x_view = 2 * (double)x / WIDTH - 1; /* MAPS X FROM -1 TO 1 */
	ray_dir.x = player->looking_dir.x + player->plane.x * x_view;
	ray_dir.y = player->looking_dir.y + player->plane.y * x_view;
	return (ray_dir);
}

void		set_wall_height(int *draw_start, int *draw_end, int line_height)
{
	*draw_start = (-line_height / 2 + HEIGHT / 2);
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (line_height / 2 + HEIGHT / 2);
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

t_point	calc_step_dir(t_player *player, t_dpoint ray_dir, t_dpoint *side_dist, t_dpoint delta_dist, t_point map_pos)
{
	t_point step;

	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist->x = (player->pos.x - map_pos.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist->x = (map_pos.x + 1.0 - player->pos.x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist->y = (player->pos.y - map_pos.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist->y = (map_pos.y + 1.0 - player->pos.y) * delta_dist.y;
	}
	return (step);
}

int		wall_hit(int **map, t_dpoint side_dist, t_dpoint delta_dist, t_point *map_pos, t_point step)
{
	int hit;
	int side;

	hit = 0;
	while (!hit)
	{
		if (side_dist.y < side_dist.x)
		{
			side_dist.y += delta_dist.y;
			map_pos->y += step.y;
			side = 0;
		}
		else
		{
			side_dist.x += delta_dist.x;
			map_pos->x += step.x;
			side = 1;
		}
		if (map[map_pos->y][map_pos->x] > 0 && map[map_pos->y][map_pos->x] <= WALLCOUNT)
			hit = 1;
	}
	return (side);
}
