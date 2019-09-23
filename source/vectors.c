/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:52:03 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/23 12:04:46 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

t_dpoint	get_unit_x(double rot)
{
	t_dpoint v;

	v.x = cos(rot);
	v.y = sin(rot);
	return (v);
}

t_dpoint	get_unit_y(double rot)
{
	t_dpoint v;

	v.x = -sin(rot);
	v.y = cos(rot);
	return (v);
}

void		multiply_vector(double m, t_dpoint *vector)
{
	vector->x *= m;
	vector->y *= m;
}

t_dpoint	add_vector(t_dpoint *a, t_dpoint *b)
{
	t_dpoint sum;

	sum.x = a->x + b->x;
	sum.y = a->y + b->y;
	return (sum);
}

t_dpoint	sub_vector(t_dpoint *a, t_dpoint *b)
{
	t_dpoint sub;

	sub.x = a->x - b->x;
	sub.y = a->y - b->y;
	return (sub);
}
