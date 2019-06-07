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
		PLAYER->pos.y += 0.1;
	if (key == KEY_W)
		PLAYER->pos.y -= 0.1;
	if (key == KEY_D)
		PLAYER->pos.x += 0.1;
	if (key == KEY_A)
		PLAYER->pos.x -= 0.1;
	return (0);
}

int	key_release(int key, t_mlx *mlx)
{
	return (0);
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	return (0);
}
