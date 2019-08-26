#include "wolf3d.h"
#include <math.h>
#include <stdlib.h>

void	calculate_relative_positions(t_mlx *mlx)
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

int		compare_mapobject_distance(const void *a, const void *b)
{
	double diff = ((t_mapobject*)a)->rel_loc.y - ((t_mapobject*)b)->rel_loc.y;
	return diff > 0 ? -1 : (diff == 0 ? 0 : 1);
}

void	set_sprite_width(int *start, int *end, t_dpoint *location)
{
	*start = (int)((((location->x - 0.5) / (location->y * 0.66)) + 1) * (WIDTH / 2)); // Maps it to a number from 0 - WIDTH
	*end = (int)((((location->x + 0.5) / (location->y * 0.66)) + 1) * (WIDTH / 2));
}

int		max(int a, int b)
{
	return (a > b ? a : b);
}

int		min(int a, int b)
{
	return (a < b ? a : b);
}

void	render_sprite(t_mlx *mlx, t_mapobject *object)
{
	int start;
	int end;
	int sprite_height;
	int draw_start;
	int draw_end;

	set_sprite_width(&start, &end, &object->rel_loc);
	if (start >= WIDTH || end < 0) // Out of view
		return ;
	sprite_height = (int)((2 * HEIGHT) / object->rel_loc.y);
	set_wall_height(&draw_start, &draw_end, sprite_height);

	int x = max(0, start);
	int x_end = min(end, WIDTH);

	 while(x < x_end)
	 {
		 int texture_x = ((x - start) * object->sprite.width) / (end - start);
		 if (object->rel_loc.y < mlx->z[x])
		 	draw_sprite(mlx, (int[2]){draw_start, draw_end}, sprite_height, &object->sprite, x, texture_x);
		 x++;
	 }
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
		render_sprite(mlx, &mlx->objects[i]);
		i++;
	}
}
