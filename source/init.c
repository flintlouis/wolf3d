#include "wolf3d.h"

void	run_wolf(t_mlx *mlx)
{
	// mlx_hook(mlx->win, 4, 1L << 2, mouse_press, mlx);
	// mlx_hook(mlx->win, 5, 1L << 3, mouse_release, mlx);
	// mlx_hook(mlx->win, 6, 1L << 6, mouse_move, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_window, NULL);
	mlx_loop(mlx->mlx);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Wolf3d");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->data_addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
}

void	init_wolf(char *map)
{
	t_mlx *mlx;

	mlx = MEM(t_mlx);
	init_mlx(mlx);
	run_wolf(mlx);
}