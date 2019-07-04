#include "wolf3d.h"
#include <stdlib.h>

int	close_window(void *ptr)
{
	(void)ptr;
	exit(0);
	return (0);
}

/* Handles player movement + checks for wall collisions */
static void move(t_dpoint *direction, t_mlx *mlx, int sign)
{
	double tmpy;
	double tmpx;
	int speed;

	speed = 10;
	if (PLAYER->run)
		speed = 6;
	tmpy = PLAYER->pos.y + sign * (direction->y / speed);
	tmpx = PLAYER->pos.x + sign * (direction->x / speed);
	if (!MAP[(int)(tmpy)][(int)(PLAYER->pos.x)])
		PLAYER->pos.y = tmpy;
	if (!MAP[(int)(PLAYER->pos.y)][(int)(tmpx)])
		PLAYER->pos.x = tmpx;
}

int	key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		close_window(NULL);
	if (key == KEY_S)
		move(&PLAYER->looking_dir, mlx, -1);
	if (key == KEY_W)
		move(&PLAYER->looking_dir, mlx, 1);
	if (key == KEY_D)
		move(&PLAYER->plane, mlx, 1);
	if (key == KEY_A)
		move(&PLAYER->plane, mlx, -1);
	if (key == KEY_UP)
		PLAYER->look += 10;
	if (key == KEY_DOWN)
		PLAYER->look -= 10;
	if (key == KEY_RIGHT)
		rotate_right(mlx, 1);
	if (key == KEY_LEFT)
		rotate_left(mlx, -1);
	if (key == KEY_LSHIFT)
		PLAYER->run = 1;	
	return (0);
}

int	key_release(int key, t_mlx *mlx)
{
	if (key == KEY_LSHIFT)
		PLAYER->run = 0;
	return (0);
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	static int prevx;

	if (x < prevx)
		rotate_left(mlx, -2.5);
	else if (x > prevx)
		rotate_right(mlx, 2.5);
	prevx = x;
	return (0);
}
