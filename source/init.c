#include "wolf3d.h"
#include "mlx.h"

static void	run_wolf(t_mlx *mlx)
{
	// mlx_hook(mlx->win, 4, 1L << 2, mouse_press, mlx);
	// mlx_hook(mlx->win, 5, 1L << 3, mouse_release, mlx);
	mlx_hook(mlx->win, 6, 1L << 6, mouse_move, mlx);
	mlx_loop_hook(mlx->mlx, raycaster, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_window, NULL);
	mlx_loop(mlx->mlx);
}

static void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "WOLF3D");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->data_addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
}

static t_player *init_player(void)
{
	t_player *player;

	player = MEM(t_player);
	/* WHERE THE PLAYER SPAWNS ON MAP */
	player->pos.x = 10;
	player->pos.y = 12;

	/* ??? SOMETHING TO DO WITH PLANE */
	player->plane.x = 0.66;
	player->plane.y = 0;

	/* WHICH WAY THE PLAYER I LOOKING */
	player->looking_dir.x = 0;
	player->looking_dir.y = -1;

	player->look = 4;
	return(player);
}

void	init_wolf(char *map)
{
	t_mlx *mlx;

	mlx = MEM(t_mlx);
	init_mlx(mlx);
	mlx->map = get_map(map);
	mlx->player = init_player();
	run_wolf(mlx);
}
