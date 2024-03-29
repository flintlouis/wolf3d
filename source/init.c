/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:24 by fhignett       #+#    #+#                */
/*   Updated: 2019/10/07 12:06:23 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <time.h>

static void	run_wolf(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, wolfenstein, mlx);
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
	mlx->data_addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel),
	&(mlx->size_line), &(mlx->endian));
	mlx->z = (double*)ft_memalloc(sizeof(double) * WIDTH);
	mlx->sprite = MEM(t_sprite);
}

static void	init_mapobjects(t_mlx *mlx)
{
	int i;
	int j;
	int obj_index;

	i = 0;
	obj_index = 0;
	OBJECTS =
	(t_mapobject*)ft_memalloc(sizeof(t_mapobject) * LEVEL->object_count);
	while (i < LEVEL->size.y)
	{
		j = 0;
		while (j < LEVEL->size.x)
		{
			if (MAP[i][j] > WALLCOUNT)
			{
				OBJECTS[obj_index].id = MAP[i][j];
				OBJECTS[obj_index].location.x = j + 0.5;
				OBJECTS[obj_index].location.y = i + 0.5;
				OBJECTS[obj_index].sprite = TEXTURES[MAP[i][j] - 1];
				obj_index++;
			}
			j++;
		}
		i++;
	}
}

void		init_wolf(char *map)
{
	t_mlx *mlx;

	srand(time(0));
	mlx = MEM(t_mlx);
	init_mlx(mlx);
	LEVEL = MEM(t_level);
	PLAYER = MEM(t_player);
	init_level(mlx, map);
	if (ft_strequ("level.test", map))
		LEVEL->l = 3;
	else if (ft_strequ("level.survival", map))
		LEVEL->l = 2;
	set_player_angle(PLAYER, PLAYER->angle);
	CONTROLS = MEM(t_controls);
	TEXTURES = get_textures("source/textures.txt");
	GUN = get_textures("source/guns.txt");
	init_mapobjects(mlx);
	ENEMIES = (t_enemy*)ft_memalloc(sizeof(t_enemy) * LEVEL->enemy_count);
	init_pathfinding(mlx);
	PLAYER->health = 100;
	mlx->gun_size = (WIDTH + HEIGHT) / 160;
	run_wolf(mlx);
}
