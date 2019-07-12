#include "wolf3d.h"
#include <math.h>

static double to_radians(double degrees)
{
    return (degrees * (M_PI / 180.0));
}

void	rotate(t_mlx *mlx, double degrees)
{
	double tmpx;
	double deg;

	deg = to_radians(degrees);
	tmpx = PLAYER->looking_dir.x;
	PLAYER->looking_dir.x = tmpx * cos(deg) - PLAYER->looking_dir.y * sin(deg);
	PLAYER->looking_dir.y = tmpx * sin(deg) + PLAYER->looking_dir.y * cos(deg);

	tmpx = PLAYER->plane.x;
	PLAYER->plane.x = tmpx * cos(deg) - PLAYER->plane.y * sin(deg);
	PLAYER->plane.y = tmpx * sin(deg) + PLAYER->plane.y * cos(deg);
}

void	player_look(t_mlx *mlx)
{
	if (CONTROLS->look_right)
		rotate(mlx, 1.5);
	if (CONTROLS->look_left)
		rotate(mlx, -1.5);
}