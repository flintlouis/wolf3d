#include "wolf3d.h"
#include <math.h>
#include <stdlib.h>

static void	calculate_relative_positions(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < LEVEL->object_count)
	{
		t_mapobject *current = &mlx->objects[i];
		current->rel_loc = sub_vector(&current->location, &PLAYER->pos);
		rotate_vector(&current->rel_loc, to_radians(-PLAYER->angle));
		current->rel_loc.x *= -1;
		i++;
	}
}

static int		compare_mapobject_distance(const void *a, const void *b)
{
	double diff = ((t_mapobject*)a)->rel_loc.y - ((t_mapobject*)b)->rel_loc.y;
	return diff > 0 ? -1 : (diff == 0 ? 0 : 1);
}

static void	set_sprite_width(int *start, int *end, t_dpoint *location)
{
	*start = (int)((((location->x - 0.5) / (location->y * 0.66)) + 1) * (WIDTH / 2)); // Maps it to a number from 0 - WIDTH
	*end = (int)((((location->x + 0.5) / (location->y * 0.66)) + 1) * (WIDTH / 2));
}

static void *draw_sprite(void *data)
{
	t_mlx *mlx;

	mlx = (t_mlx*)data;
	while(mlx->x[0] < mlx->x[1])
	{
		int texture_x = ((mlx->x[0] - SPRITE->start) * OBJECTS[SPRITE->id].sprite.width) / (SPRITE->end - SPRITE->start);
		if (OBJECTS[SPRITE->id].rel_loc.y < mlx->z[mlx->x[0]])
			draw_object(mlx, &OBJECTS[SPRITE->id].sprite, mlx->x[0], (t_draw){SPRITE->height, SPRITE->draw_start, SPRITE->draw_end, texture_x, 0});
		mlx->x[0]++;
	}
	return (0);
}

static void sprite_threading(t_mlx *mlx, void*(*f)(void*), int x, int x_end)
{
	int			i;
	t_mlx		data[THREAD];
	pthread_t	threads[THREAD];
	int v;

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

static void	render_sprite(t_mlx *mlx)
{
	set_sprite_width(&SPRITE->start, &SPRITE->end, &OBJECTS[SPRITE->id].rel_loc);
	if (SPRITE->start >= WIDTH || SPRITE->end < 0) // Out of view
		return ;
	SPRITE->height = (int)((/* 2 * */ HEIGHT) / OBJECTS[SPRITE->id].rel_loc.y);
	set_wall_height(&SPRITE->draw_start, &SPRITE->draw_end, SPRITE->height);

	sprite_threading(mlx, draw_sprite, ft_max(0, SPRITE->start), ft_min(SPRITE->end, WIDTH));
}

void	spritecaster(t_mlx *mlx)
{
	int i;

	calculate_relative_positions(mlx);
	qsort((void*)mlx->objects, LEVEL->object_count, sizeof(t_mapobject), compare_mapobject_distance);

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
