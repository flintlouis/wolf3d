#include "wolf3d.h"
#include <math.h>



int compare_nodes(t_node *s1, t_node *s2);
int in_set(t_node **set, t_node *node);
void add_node(t_node **set, t_node *node);
void rm_node(t_node **set, t_node *node);


static double heuristic(t_node *a, t_node *b)
{
	double d;
	// double dx;
	// double dy;

	// dx = (double)b->loc.x - a->loc.x;
	// dy = (double)b->loc.y - a->loc.y;
	// d = sqrt(((dx*dx)+(dy*dy))); /* Euclidian distance */
	d = abs(a->loc.x - b->loc.x) + abs(a->loc.y - b->loc.y); /* Taxi distance */
	return (d);
}

static void update_node(t_node *neighbor, t_node *node, double g, t_node *end)
{
	neighbor->g = g;
	neighbor->h = heuristic(neighbor, end);
	neighbor->f = neighbor->g + neighbor->h;
	neighbor->prev = node;

}

static void add_to_openSet(t_node *node, t_node **openSet, t_node **closedSet, t_node *end)
{
	t_node **nbs = node->neighbors;
	int i = 0;
	double tmpG;
	while (i < 4)
	{
		if (nbs[i] && !in_set(closedSet, nbs[i]))
		{
			tmpG = node->g + 1;
			if (in_set(openSet, nbs[i]))
			{
				if (tmpG < nbs[i]->g)
					update_node(nbs[i], node, tmpG, end);
			}
			else
			{
				update_node(nbs[i], node, tmpG, end);
				add_node(openSet, nbs[i]);
			}
		}
		i++;
	}
}

void find_path(t_node **openSet, t_node **closedSet, t_node **path, t_node *end)
{
	t_node *tmp;
	t_node *node;

	node = *openSet;
	tmp = *openSet;
	while (tmp)
	{
		if (tmp->f < node->f)
			node = tmp;
		tmp = tmp->next;
	}
	rm_node(openSet, node);
	add_node(closedSet, node);
	if (compare_nodes(node, end))
	{
		*path = node;
		return ;
	}
	add_to_openSet(node, openSet, closedSet, end);
}
