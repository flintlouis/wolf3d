#include "wolf3d.h"
#include "mlx.h"
#include <math.h>

#define MAP mlx->map->map
void    draw_line(t_mlx *mlx, t_point a, t_point b, t_colour colour);

double	to_radians(int degrees)
{
	return (degrees * (PI / 180));
}

int	raycaster(t_mlx *mlx)
{
	// int map[7][7] = 
	// {
	// 	{1, 1, 1, 1, 1, 1, 1},
	// 	{1, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, 1, 1, 1, 1},
	// };
	double x_intersect;
	double y_intersect;
	double pos_y;
	double pos_x;
	double dir_x;
	double dir_y;
	double plane_x, plane_y;
	double dy;
	double dx;
	double cur_time;
	double old_time;
	double camera_x;
	double camera_y;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	/* DISTANCE FROM PLAYER TO GRID CROSS X OR Y */
	double side_dist_x;
	double side_dist_y;
	/* what direction to step in x or y-direction (either +1 or -1) */
	int step_x;
	int step_y;
	int hit;
	int side; /* NS WALL HIT? OR EW WALL HIT? */
	double perp_wall_dist;
	double delta_dist_x;
	double delta_dist_y;
	int line_height;
	int draw_start;
	int draw_end;
	t_colour colour;

	pos_x = 10;
	pos_y = 12;
	dir_x = -1;
	dir_y = 0;
	plane_x = 0;
	plane_y = 0.66;
	old_time = 0;
	cur_time = 0;

	ft_bzero(mlx->data_addr, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
	/* PLANE */
	for (int x = 0; x < WIDTH; x++)
	{
		/* mapt viewing plane van -1 naar 1 */
		camera_x = 2 * x / (double)WIDTH - 1;
		ray_dir_x = dir_x + plane_x * camera_x;
		ray_dir_y = dir_y + plane_y * camera_y;

		/* WHICH BOX THE PLAYER IS STANDING IN */
		map_x = (int)pos_x;
		map_y = (int)pos_y;


		/* DISTANCE FROM X/Y SIDE TO OTHER X/Y SIDE */
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);

		hit = 0;

		/* CALC STEP FOR MAP + INIT SIDE_DIST */
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}

		/* WHILE NO WALL HIT */
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (MAP[map_y][map_x] > 0)
				hit = 1;
		}

		/* CALCULATE DISTANCE PROJECTED ON CAMERA DIRECTION */
		if (side == 0)
			perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;
		
		/* FOR HIGHER/LOWER WALLS DO FOR EXAMPLE 2*HEIGHT */
		line_height = (int)(HEIGHT / perp_wall_dist);

		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		switch (MAP[map_x][map_y])
		{
		case 1: colour = (t_colour){125,125,125}; 
			break;
		case 2: colour = (t_colour){125,0,0}; 
			break;
		case 3: colour = (t_colour){0,125,0}; 
			break;
		case 4: colour = (t_colour){0,0,125};
			break;
		default: colour = (t_colour){125,125,0};
			break;
		}
		if (side == 1)
		{
			colour.r /= 2;
			colour.g /= 2;
			colour.b /= 2;
		}
		ft_printf("x = %d, draw_start = %d, draw_end = %d\n", x, draw_start, draw_end);
		draw_line(mlx, (t_point){x, draw_start}, (t_point){x, draw_end}, colour);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
