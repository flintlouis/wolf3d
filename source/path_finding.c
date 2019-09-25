/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_finding.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:48 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/25 11:25:04 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>
#include <stdlib.h>

/*
** Taxi distance
*/

static double	heuristic(t_node *a, t_node *b)
{
	double d;

	d = abs(a->loc.x - b->loc.x) + abs(a->loc.y - b->loc.y);
	return (d);
}

/*
** Update Node
*/

static void		update(t_node *neighbor, t_node *node, double g, t_node *end)
{
	neighbor->g = g;
	neighbor->h = heuristic(neighbor, end);
	neighbor->f = neighbor->g + neighbor->h;
	neighbor->prev = node;
}

static	void	add_to_openset(t_node *node, t_node **open_set,
t_node **closed_set, t_node *end)
{
	int		i;
	double	tmpg;
	t_node	**nbs;

	i = 0;
	nbs = node->neighbors;
	while (i < 4)
	{
		if (nbs[i] && !in_set(closed_set, nbs[i]))
		{
			tmpg = node->g + 1;
			if (in_set(open_set, nbs[i]))
			{
				if (tmpg < nbs[i]->g)
					update(nbs[i], node, tmpg, end);
			}
			else
			{
				update(nbs[i], node, tmpg, end);
				add_node(open_set, nbs[i]);
			}
		}
		i++;
	}
}

void			find_path(t_node **open_set, t_node **closed_set,
t_node **path, t_node *end)
{
	t_node *tmp;
	t_node *node;

	node = *open_set;
	tmp = *open_set;
	while (tmp)
	{
		if (tmp->f < node->f)
			node = tmp;
		tmp = tmp->next;
	}
	rm_node(open_set, node);
	add_node(closed_set, node);
	if (compare_nodes(node, end))
	{
		*path = node;
		return ;
	}
	add_to_openset(node, open_set, closed_set, end);
}
