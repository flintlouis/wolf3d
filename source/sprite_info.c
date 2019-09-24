/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_info.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/24 12:14:17 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/24 12:16:55 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

/*
** Calculate the relative positions of the sprites compared to the player
*/

void		calculate_relative_positions(t_mlx *mlx)
{
	int			i;
	t_mapobject *current;

	i = 0;
	while (i < LEVEL->object_count)
	{
		current = &mlx->objects[i];
		current->rel_loc = sub_vector(&current->location, &PLAYER->pos);
		rotate_vector(&current->rel_loc, to_radians(-PLAYER->angle));
		current->rel_loc.x *= -1;
		i++;
	}
}

/*
** return (diff > 0 ? -1 : (diff == 0 ? 0 : 1));
*/

int			compare_mapobject_distance(const void *a, const void *b)
{
	double diff;

	diff = ((t_mapobject*)a)->rel_loc.y - ((t_mapobject*)b)->rel_loc.y;
	if (diff > 0)
		return (-1);
	else if (diff == 0)
		return (0);
	else
		return (1);
}

/*
** Maps it to a number from 0 - WIDTH
*/

void		set_sprite_width(int *start, int *end, t_dpoint *location)
{
	*start = (int)((((location->x - 0.5)
	/ (location->y * 0.66)) + 1) * (WIDTH >> 1));
	*end = (int)((((location->x + 0.5)
	/ (location->y * 0.66)) + 1) * (WIDTH >> 1));
}
