#include "wolf3d.h"

/* Handles player movement + checks for wall collisions */
static void move(t_dpoint *move, t_mlx *mlx, int direction)
{
	double tmpy;
	double tmpx;
	int speed;

	speed = 20;
	if (CONTROLS->run)
		speed = 10;
	tmpy = PLAYER->pos.y + direction * (move->y / speed);
	tmpx = PLAYER->pos.x + direction * (move->x / speed);
	if (MAP[(int)(tmpy)][(int)(PLAYER->pos.x)] == 0)
		PLAYER->pos.y = tmpy;
	if (MAP[(int)(PLAYER->pos.y)][(int)(tmpx)] == 0)
		PLAYER->pos.x = tmpx;
}

/* Makes movement smoother */
void	move_player(t_mlx *mlx)
{
	if (CONTROLS->front)
		move(&PLAYER->looking_dir, mlx, 1);
	if (CONTROLS->back)
		move(&PLAYER->looking_dir, mlx, -1);
	if (CONTROLS->left)
		move(&PLAYER->plane, mlx, -1);
	if (CONTROLS->right)
		move(&PLAYER->plane, mlx, 1);
}

