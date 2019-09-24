/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spritecaster.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:58 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/24 12:15:49 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdlib.h>

static void		*draw_sprite(void *data)
{
	int		texture_x;
	t_mlx	*mlx;

	mlx = (t_mlx*)data;
	while (mlx->x[0] < mlx->x[1])
	{
		texture_x = ((mlx->x[0] - SPRITE->start) *
		OBJECTS[SPRITE->id].sprite.width) / (SPRITE->end - SPRITE->start);
		if (OBJECTS[SPRITE->id].rel_loc.y < mlx->z[mlx->x[0]])
			draw_object(mlx, &OBJECTS[SPRITE->id].sprite, mlx->x[0],
			(t_draw){SPRITE->height, SPRITE->draw_start,
			SPRITE->draw_end, texture_x, 0});
		mlx->x[0]++;
	}
	return (0);
}

static	void	sprite_threading(t_mlx *mlx, void *(*f)(void*),
int x, int x_end)
{
	int			i;
	int			v;
	t_mlx		data[THREAD];
	pthread_t	threads[THREAD];

	i = 0;
	v = (x_end - x) / THREAD;
	while (i < THREAD)
	{
		ft_memcpy(&data[i], mlx, sizeof(t_mlx));
		data[i].x[0] = x + (v * i);
		data[i].x[1] = i == THREAD - 1 ? x_end : x + (v * (i + 1));
		pthread_create(&threads[i], NULL, f, &data[i]);
		i++;
	}
	join_threads(i, threads);
}

/*
** If start >= then Width or end < 0 it means they're not on the screen
*/

static	void	render_sprite(t_mlx *mlx)
{
	set_sprite_width(&SPRITE->start, &SPRITE->end,
	&OBJECTS[SPRITE->id].rel_loc);
	if (SPRITE->start >= WIDTH || SPRITE->end < 0)
		return ;
	SPRITE->height = (int)((HEIGHT) / OBJECTS[SPRITE->id].rel_loc.y);
	set_wall_height(&SPRITE->draw_start, &SPRITE->draw_end, SPRITE->height);
	sprite_threading(mlx, draw_sprite, ft_max(0, SPRITE->start),
	ft_min(SPRITE->end, WIDTH));
}

/*
** Put the enemy sprites in a pointer array
*/

static	void	init_enemies(t_mlx *mlx, t_mapobject *objects)
{
	int i;
	int enemy_index;

	i = 0;
	enemy_index = 0;
	while (i < LEVEL->object_count)
	{
		if (objects[i].id == ENEMY)
		{
			ENEMIES[enemy_index].ss = &OBJECTS[i];
			enemy_index++;
		}
		i++;
	}
}

/*
** Calculate the relative position of each sprite and sort it
** into an array from furthest away to closest
** Then render sprites from furthest to closest and break if rel-pos.y
** is less then 0, which means that they are behind the player
*/

void			spritecaster(t_mlx *mlx)
{
	int i;

	calculate_relative_positions(mlx);
	qsort((void*)OBJECTS, LEVEL->object_count,
	sizeof(t_mapobject), compare_mapobject_distance);
	init_enemies(mlx, OBJECTS);
	i = 0;
	while (i < LEVEL->object_count)
	{
		if (mlx->objects[i].rel_loc.y <= 0)
			break ;
		SPRITE->id = i;
		render_sprite(mlx);
		i++;
	}
}
