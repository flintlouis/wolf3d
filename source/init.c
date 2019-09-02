#include "wolf3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <time.h>

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
	mlx->z = (double*)ft_memalloc(sizeof(double) * WIDTH);
	mlx->sprite = MEM(t_sprite);
}

static void init_mapobjects(t_mlx *mlx)
{
	int i;
	int j;
	int obj_index;
	int enemy_index;

	i = 0;
	enemy_index = 0;
	obj_index = 0;
	OBJECTS = (t_mapobject*)ft_memalloc(sizeof(t_mapobject) * LEVEL->object_count);
	ENEMIES = (t_mapobject**)ft_memalloc(sizeof(t_mapobject*) * LEVEL->enemy_count);
	while (i < LEVEL->size.y)
	{
		j = 0;
		while (j < LEVEL->size.x)
		{
			if (MAP[i][j] > WALLCOUNT)
			{
				OBJECTS[obj_index].location.x = j + 0.5;
				OBJECTS[obj_index].location.y = i + 0.5;
				OBJECTS[obj_index].sprite = TEXTURES[MAP[i][j] - 1];
				if (MAP[i][j] == ENEMY)
				{
					ENEMIES[enemy_index] = &OBJECTS[obj_index];
					enemy_index++;
				}
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

	srand(time(0));
	mlx = MEM(t_mlx);
	init_mlx(mlx);
	init_level(mlx, map);
	CONTROLS = MEM(t_controls);
	TEXTURES = get_textures("source/textures.txt");
	GUN = get_textures("source/guns.txt");
	init_mapobjects(mlx);
	// init_enemies(mlx);
	run_wolf(mlx);
}
