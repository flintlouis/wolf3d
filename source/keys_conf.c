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
		mlx->player->pos_x += 0.1;
	if (key == KEY_W)
		mlx->player->pos_x -= 0.1;
	if (key == KEY_D)
		mlx->player->pos_y += 0.1;
	if (key == KEY_A)
		mlx->player->pos_y -= 0.1;
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
