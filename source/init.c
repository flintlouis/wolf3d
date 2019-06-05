#include "wolf3d.h"
#include "mlx.h"

static void	run_wolf(t_mlx *mlx)
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
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "WOLF3D");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->data_addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
}

void	init_wolf(char *map)
{
	t_mlx *mlx;

	mlx = MEM(t_mlx);
	init_mlx(mlx);
	mlx->map = get_map(map);
///////////////////////
	ft_printf("width = %d, height = %d\n\n", mlx->map->width, mlx->map->height);
	int i = 0;
	int j = 0;
	while (j < mlx->map->height)
	{
		while (i < mlx->map->width)
		{
			ft_printf("%d ", mlx->map->map[j][i]);
			i++;
		}
		ft_putendl("");
		j++;
		i = 0;
	}
//////////////////////
	run_wolf(mlx);
}