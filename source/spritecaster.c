#include "wolf3d.h"
#include <math.h>

static double	calc_wall_distance(t_player *player, int side, t_point map_pos, t_point step, t_dpoint ray_dir)
{
	if (side == 0)
		return ((map_pos.y - player->pos.y + (1 - step.y) / 2) / ray_dir.y);
	else
		return ((map_pos.x - player->pos.x + (1 - step.x) / 2) / ray_dir.x);

}

static t_dpoint	set_raydir(int x, t_player *player)
{
	double		x_view;
	t_dpoint	ray_dir;

	x_view = 2 * (double)x / WIDTH - 1; /* MAPS X FROM -1 TO 1 */
	ray_dir.x = player->looking_dir.x + player->plane.x * x_view;
	ray_dir.y = player->looking_dir.y + player->plane.y * x_view;
	return (ray_dir);
}

static void		set_wall_height(t_player *player, int *draw_start, int *draw_end, int line_height)
{
	*draw_start = (-line_height / 2 + HEIGHT / 2);
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (line_height / 2 + HEIGHT / 2);
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

static t_point	calc_step_dir(t_player *player, t_dpoint ray_dir, t_dpoint *side_dist, t_dpoint delta_dist, t_point map_pos)
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

static int		wall_hit(int **map, t_dpoint side_dist, t_dpoint delta_dist, t_point *map_pos, t_point step)
{
	int hit;

	hit = 0;
	while (!hit)
	{
		if (side_dist.y < side_dist.x)
		{
			side_dist.y += delta_dist.y;
			map_pos->y += step.y;
		}
		else
		{
			side_dist.x += delta_dist.x;
			map_pos->x += step.x;
		}
		if (map[map_pos->y][map_pos->x] > 5)
			break ;
		else if (map[map_pos->y][map_pos->x] > 0)
			hit = 1;
	}
	return (hit);
}

void			*spritecaster(void *data)
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
		if (wall_hit(MAP, side_dist, delta_dist, &map_pos, step))
		{
			mlx->x[0]++;
			continue ;
		}

		/* Distance between 2 vectors: √(x2-x1)^2+(y2-y1)^2 */
		wall_distance = sqrt(pow(((double)map_pos.x - PLAYER->pos.x), 2) + pow((map_pos.y - PLAYER->pos.y), 2));
		
		/* MULTIPLY HEIGHT FOR BIGGER WALLS */
		wall_height = (int)((2 * HEIGHT) / wall_distance);

		/* SET HEIGHT OF WALLS TOO DRAW */
		set_wall_height(PLAYER, &draw_start, &draw_end, wall_height);

		////////////////////////////////////////////////////////////////////////////////////////////////////////// DRAW TEXTURES
		int texture;
		double wall_coll; /* Where exactly the wall was hit */
		int texture_x;

		texture = MAP[map_pos.y][map_pos.x] - 1;
		if (side == 0)
			wall_coll = PLAYER->pos.x + wall_distance * ray_dir.x;
		else
			wall_coll = PLAYER->pos.y + wall_distance * ray_dir.y;
		wall_coll -= floor(wall_coll);

		texture_x = (int)(wall_coll * TEXTURES[texture].width);
		if ((side == 0 && ray_dir.y > 0) || (side == 1 && ray_dir.x < 0))
			texture_x = TEXTURES[texture].width - texture_x - 1;
		
		draw_texture(mlx, (int[2]){draw_start, draw_end}, wall_height, texture, side, mlx->x[0], texture_x);
		mlx->x[0]++;
	}
	return (0);
}