#include "wolf3d.h"
#include "mlx.h"
#include <math.h>

static double to_radians(double degrees)
{
    return (degrees * (M_PI / 180.0));
}

void	rotate_left(t_mlx *mlx)
{
	double tmpx;
	double deg;

	deg = to_radians(-1);
	tmpx = PLAYER->looking_dir.x;
	PLAYER->looking_dir.x = tmpx * cos(deg) - PLAYER->looking_dir.y * sin(deg);
	PLAYER->looking_dir.y = tmpx * sin(deg) + PLAYER->looking_dir.y * cos(deg);

	tmpx = PLAYER->plane.x;
	PLAYER->plane.x = tmpx * cos(deg) - PLAYER->plane.y * sin(deg);
	PLAYER->plane.y = tmpx * sin(deg) + PLAYER->plane.y * cos(deg);
}

void	rotate_right(t_mlx *mlx)
{
	double tmpx;
	double deg;

	deg = to_radians(1);
	tmpx = PLAYER->looking_dir.x;
	PLAYER->looking_dir.x = tmpx * cos(deg) - PLAYER->looking_dir.y * sin(deg);
	PLAYER->looking_dir.y = tmpx * sin(deg) + PLAYER->looking_dir.y * cos(deg);

	tmpx = PLAYER->plane.x;
	PLAYER->plane.x = tmpx * cos(deg) - PLAYER->plane.y * sin(deg);
	PLAYER->plane.y = tmpx * sin(deg) + PLAYER->plane.y * cos(deg);
}
