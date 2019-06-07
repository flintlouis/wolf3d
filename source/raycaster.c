#include "wolf3d.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h> /* FOR MINIMAP */

static void		mini_map(t_player *player, int **map)
{
	static int prev_pos_x;
	static int prev_pos_y;
	
	if (prev_pos_x != (int)player->pos.x || prev_pos_y != (int)player->pos.y)
	{
		system("clear");
		prev_pos_y = player->pos.y;
		prev_pos_x = player->pos.x;
		int i = 0;
		int j = 0;
		while (j < 24)
		{
			while (i < 24)
			{
				if (j == (int)player->pos.y && i == (int)player->pos.x)
					ft_printf("X ");
				else
					ft_printf("%d ", map[j][i]);
				i++;
			}
			ft_putendl("");
			j++;
			i = 0;

		}
	}
}

static void		draw_image(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_bzero(mlx->data_addr, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
}

/* CALCULATE DISTANCE PROJECTED ON CAMERA DIRECTION */
static double	calc_wall_distance(t_player *player, int side, t_point map_pos, t_point step, t_dpoint ray_dir)
{
	if (side == 0)
		return ((map_pos.y - player->pos.y + (1 - step.y) / 2) / ray_dir.y);
	else
		return ((map_pos.x - player->pos.x + (1 - step.x) / 2) / ray_dir.x);

}

static t_colour set_colour(t_mlx *mlx, t_point map_pos)
{
	if (MAP[map_pos.y][map_pos.x] == 1)
		return ((t_colour){125,125,125});
	else if (MAP[map_pos.y][map_pos.x] == 2)
		return ((t_colour){125,125,0});
	else if (MAP[map_pos.y][map_pos.x] == 3)
		return ((t_colour){0,125,125});
	else if (MAP[map_pos.y][map_pos.x] == 4)
		return ((t_colour){125,0,125});
	else
		return ((t_colour){10,10,10});
}

int				raycaster(t_mlx *mlx)
{
	int line_height;
	int draw_start;
	int draw_end;
	int hit;
	int side; /* X WALL HIT OR Y WALL HIT */
	int x;
	double camera_x;
	t_dpoint plane;
	t_dpoint dir;
	t_dpoint side_dist;	/* DISTANCE FROM PLAYER TO GRID CROSS X OR Y */
	t_dpoint delta_dist;
	t_dpoint ray_dir;
	t_colour colour;
	t_point step; /* WHAT DIRECTION TO GO X OR Y (EITHER +1 || -1) */
	t_point map_pos;

	dir.y = -1;
	dir.x = 0;
	plane.y = 0;
	plane.x = 0.66;
	x = 0;

	/* PLANE */
	while (x < WIDTH)
	{
		/* mapt viewing plane van -1 naar 1 */
		camera_x = 2 * x / (double)WIDTH - 1;
		ray_dir.y = dir.y + plane.y * camera_x;
		ray_dir.x = dir.x + plane.x * camera_x;

		/* WHICH BOX THE PLAYER IS STANDING IN */
		map_pos.y = (int)PLAYER->pos.y;
		map_pos.x = (int)PLAYER->pos.x;

		/* DISTANCE FROM X/Y SIDE TO OTHER X/Y SIDE */
		delta_dist.y = fabs(1 / ray_dir.y);
		delta_dist.x = fabs(1 / ray_dir.x);


		/* CALC STEP FOR MAP + INIT SIDE_DIST */
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (PLAYER->pos.y - map_pos.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map_pos.y + 1.0 - PLAYER->pos.y) * delta_dist.y;
		}
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (PLAYER->pos.x - map_pos.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map_pos.x + 1.0 - PLAYER->pos.x) * delta_dist.x;
		}

		/* WHILE NO WALL HIT */
		hit = 0;
		while (hit == 0)
		{
			if (side_dist.y < side_dist.x)
			{
				side_dist.y += delta_dist.y;
				map_pos.y += step.y;
				side = 0;
			}
			else
			{
				side_dist.x += delta_dist.x;
				map_pos.x += step.x;
				side = 1;
			}
			if (MAP[map_pos.y][map_pos.x] > 0)
				hit = 1;
		}
		
		/* FOR HIGHER/LOWER WALLS DO FOR EXAMPLE 2*HEIGHT */
		line_height = (int)(HEIGHT / calc_wall_distance(PLAYER, side, map_pos, step, ray_dir));

		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		/* SET COLOUR FOR NUMBER */
		colour = set_colour(mlx, map_pos);
		if (side == 1)
		{
			colour.r /= 2;
			colour.g /= 2;
			colour.b /= 2;
		}
		x++;
		draw_ver_line(mlx, (t_point){x, draw_start}, (t_point){x, draw_end}, colour);
	}
	draw_image(mlx);
	mini_map(mlx->player, MAP);
	return (0);
}
