/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotation.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:55 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/23 12:09:03 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

double		to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

/*
** ROTATE VECTOR SIMPLIFIED:
**
** void	rotate_vector(t_dpoint *vector, double rad)
** {
** 	t_dpoint ux = get_unit_x(rad);
** 	t_dpoint uy = get_unit_y(rad);
**
** 	multiply_vector(vector->x, &ux);
** 	multiply_vector(vector->y, &uy);
**
** 	t_dpoint sum = add_vector(&ux, &uy);
**
** 	vector->x = sum.x;
** 	vector->y = sum.y;
** }
*/

void		rotate_vector(t_dpoint *vector, double rad)
{
	double tmpx;

	tmpx = vector->x;
	vector->x = tmpx * cos(rad) - vector->y * sin(rad);
	vector->y = tmpx * sin(rad) + vector->y * cos(rad);
}

/*
** Reset the vector to calculate from the starting position
** Safety for the imprecise double round off
*/

static void	set_vector(t_dpoint *vector, double angle, double distance)
{
	vector->x = 0;
	vector->y = 1;
	rotate_vector(vector, to_radians(angle));
	multiply_vector(distance, vector);
}

/*
** Add 90˚ to plane because it's perpendicular to the looking direction
*/

void		set_player_angle(t_player *player, double degrees)
{
	player->angle = degrees;
	if (player->angle < 0)
		player->angle += 360;
	else if (player->angle > 360)
		player->angle -= 360;
	set_vector(&player->looking_dir, player->angle, 1);
	set_vector(&player->plane, player->angle + 90, 0.66);
}

void		player_look(t_player *player, t_controls *controls)
{
	if (controls->look_right)
		set_player_angle(player, player->angle + 1.5);
	if (controls->look_left)
		set_player_angle(player, player->angle - 1.5);
}
