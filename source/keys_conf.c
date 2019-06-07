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
	/* Handles player movement + checks for wall collisions */
	if (key == KEY_ESC)
		close_window(NULL);
	if (key == KEY_S && !MAP[(int)PLAYER->pos.y + 1][(int)(PLAYER->pos.x)])
		PLAYER->pos.y += 0.1;
	if (key == KEY_W && !MAP[(int)PLAYER->pos.y - 1][(int)(PLAYER->pos.x)])
		PLAYER->pos.y -= 0.1;
	if (key == KEY_D && !MAP[(int)(PLAYER->pos.y)][(int)(PLAYER->pos.x) + 1])
		PLAYER->pos.x += 0.1;
	if (key == KEY_A && !MAP[(int)(PLAYER->pos.y)][(int)(PLAYER->pos.x - 1)])
		PLAYER->pos.x -= 0.1;
	if (key == KEY_UP)
		PLAYER->look += 10;
	if (key == KEY_DOWN)
		PLAYER->look -= 10;
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
