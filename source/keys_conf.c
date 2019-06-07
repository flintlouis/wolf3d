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
	printf("player x:  %.1lf player y: %.1lf\n", PLAYER->pos.x, PLAYER->pos.y);
	printf("%d\n", MAP[6][12]);
	printf("%d\n", MAP[6][11]);
	printf("%d\n", MAP[6][10]);
	if (key == KEY_ESC)
		close_window(NULL);
	if (key == KEY_S && !MAP[(int)PLAYER->pos.x][(int)(PLAYER->pos.y) + 1])
		PLAYER->pos.y += 0.1;
	if (key == KEY_W && !MAP[(int)PLAYER->pos.x][(int)(PLAYER->pos.y) - 1])
	{
		printf("MAP NUMBER: %d\n", MAP[(int)(PLAYER->pos.x)][(int)(PLAYER->pos.y) - 1]);
		printf("MAP COORD: x: %d y: %d\n", (int)(PLAYER->pos.x), (int)(PLAYER->pos.y) - 1);
		PLAYER->pos.y -= 0.1;
	}
	if (key == KEY_D && !MAP[(int)(PLAYER->pos.x) + 1][(int)(PLAYER->pos.y)])
		PLAYER->pos.x += 0.1;
	if (key == KEY_A && !MAP[(int)(PLAYER->pos.x)- 1][(int)(PLAYER->pos.y)])
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
