#include "wolf3d.h"
#include <math.h>

static double	calc_wall_distance(t_player *player, int side, t_point map_pos, t_point step, t_dpoint ray_dir)
{
	if (side == 0)
		return ((map_pos.y - player->pos.y + (1 - step.y) / 2) / ray_dir.y);
	else
		return ((map_pos.x - player->pos.x + (1 - step.x) / 2) / ray_dir.x);

}

/* SET COLOUR FOR NUMBER */
static t_colour	set_colour(t_mlx *mlx, t_point map_pos, int side)
{
	t_colour colour;

	if (MAP[map_pos.y][map_pos.x] == 1)
		colour = (t_colour){125,125,125};
	else if (MAP[map_pos.y][map_pos.x] == 2)
		colour = (t_colour){125,0,0};
	else if (MAP[map_pos.y][map_pos.x] == 3)
		colour = (t_colour){0,125,125};
	else if (MAP[map_pos.y][map_pos.x] == 4)
		colour = (t_colour){125,0,125};
	else
		colour = (t_colour){212,175,55};
	if (side == 1)
	{
		colour.r /= 2;
		colour.g /= 2;
		colour.b /= 2;
	}
	return (colour);
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
	/* CHANGE THE DIVISION TO LOOK UP AND DOWN */
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
	int side;

	hit = 0;
	while (hit == 0)
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
		if (map[map_pos->y][map_pos->x] > 0)
			hit = 1;
	}
	return (side);
}

void	draw_texture(t_mlx *mlx, t_point a, t_point b, int id);//////////////////////
void			raycaster(t_mlx *mlx)
{
	int draw_start;
	int draw_end;
	int side;
	int x;

	t_dpoint side_dist;
	t_dpoint delta_dist;
	t_dpoint ray_dir;

	t_point step;
	t_point map_pos;

	x = 0;
	/* PLANE */
	while (x < WIDTH)
	{
		/* CALC VECTOR FOR RAY ON PLANE POS */
		ray_dir = set_raydir(x, PLAYER);

		/* WHICH BOX THE PLAYER IS STANDING IN */
		map_pos = (t_point){(int)PLAYER->pos.x, (int)PLAYER->pos.y};

		/* DISTANCE FROM X/Y SIDE TO OTHER X/Y SIDE */
		delta_dist = (t_dpoint){fabs(1 / ray_dir.x), fabs(1 / ray_dir.y)};

		/* CALC STEP FOR MAP + INIT SIDE_DIST */
		step = calc_step_dir(PLAYER, ray_dir, &side_dist, delta_dist, map_pos);

		/* X OR Y WALL HIT */
		side = wall_hit(MAP, side_dist, delta_dist, &map_pos, step);

		/* SET HEIGHT OF WALLS TOO DRAW */		/* MULTIPLY HEIGHT FOR BIGGER WALLS */
		set_wall_height(PLAYER, &draw_start, &draw_end, (int)((2 * HEIGHT) / calc_wall_distance(PLAYER, side, map_pos, step, ray_dir)));
	
		draw_ver_line(mlx, (t_point){x, draw_start}, (t_point){x, draw_end}, set_colour(mlx, map_pos, side));
		// draw_texture(mlx, (t_point){x, draw_start}, (t_point){x, draw_end}, MAP[map_pos.y][map_pos.x]);
		x++;
	}
}
