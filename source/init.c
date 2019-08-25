#include "wolf3d.h"
#include "mlx.h"
#include <time.h>
#include <stdlib.h>

static void	run_wolf(t_mlx *mlx)
{
	// mlx_hook(mlx->win, 4, 1L << 2, mouse_press, mlx);
	// mlx_hook(mlx->win, 5, 1L << 3, mouse_release, mlx);
	
	mlx_loop_hook(mlx->mlx, wolfenstein, mlx);
	mlx_hook(mlx->win, 6, 1L << 6, mouse_move, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
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
	mlx->z = (double*)ft_memalloc(sizeof(double) * WIDTH);//////////////
}

static t_player *init_player(void)
{
	t_player *player;

	player = MEM(t_player);
	/* WHERE THE PLAYER SPAWNS ON MAP */
	player->pos.x = 11.5;
	player->pos.y = 12.5;

	// /* PLANE */
	// player->plane.x = 0.66;
	// player->plane.y = 0;

	// /* WHICH WAY THE PLAYER IS LOOKING */
	// player->looking_dir.x = 0;
	// player->looking_dir.y = -1;

	// player->angle = 180; //////////

	return(player);
}

static void init_mapobjects(t_mlx *mlx) ////////////
{
	int i;
	int j;
	int obj_index;

	obj_index = 0;
	i = 0;
	mlx->objects = (t_mapobject*)ft_memalloc(sizeof(t_mapobject) * mlx->object_count);
	while (i < mlx->map_height)
	{
		j = 0;
		while (j < mlx->map_width)
		{
			if (MAP[i][j] > 5)
			{
				mlx->objects[obj_index].location.x = j + 0.5;
				mlx->objects[obj_index].location.y = i + 0.5;
				mlx->objects[obj_index].sprite = TEXTURES[MAP[i][j] - 1];
				obj_index++;
			}
			j++;
		}
		i++;
	}
}

void	init_wolf(char *map)
{
	t_mlx *mlx;

	mlx = MEM(t_mlx);
	init_mlx(mlx);
	mlx->map = get_map(map, &mlx->map_height, &mlx->map_width, &mlx->object_count); ///////////
	mlx->player = init_player();
	set_player_angle(mlx, 180);
	mlx->controls = MEM(t_controls);
	mlx->textures = get_textures("source/textures.txt");
	init_mapobjects(mlx); //////////////////

	run_wolf(mlx);
}
