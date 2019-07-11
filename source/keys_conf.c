#include "wolf3d.h"
#include <stdlib.h>

int	close_window(void *ptr)
{
	(void)ptr;
	exit(0);
	return (0);
}

int	key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		close_window(NULL);
	if (key == KEY_S)
		CONTROLS->back = 1;
	if (key == KEY_W)
		CONTROLS->front = 1;
	if (key == KEY_D)
		CONTROLS->right = 1;
	if (key == KEY_A)
		CONTROLS->left = 1;
	if (key == KEY_RIGHT)
		CONTROLS->look_right = 1;
	if (key == KEY_LEFT)
		CONTROLS->look_left = 1;
	if (key == KEY_LSHIFT)
		CONTROLS->run = 1;
	return (0);
}

int	key_release(int key, t_mlx *mlx)
{
	if (key == KEY_LSHIFT)
		CONTROLS->run = 0;
	if (key == KEY_W)
		CONTROLS->front = 0;
	if (key == KEY_S)
		CONTROLS->back = 0;
	if (key == KEY_A)
		CONTROLS->left = 0;
	if (key == KEY_D)
		CONTROLS->right = 0;
	if (key == KEY_LEFT)
		CONTROLS->look_left = 0;
	if (key == KEY_RIGHT)
		CONTROLS->look_right = 0;
	return (0);
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	return (0);
}
