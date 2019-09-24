/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:46 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/24 11:25:12 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		compare_nodes(t_node *s1, t_node *s2)
{
	if (!s1 || !s2)
		return (0);
	if (s1->loc.x == s2->loc.x && s1->loc.y == s2->loc.y)
		return (1);
	return (0);
}

/*
** Check if given node is in given set
*/

int		in_set(t_node **set, t_node *node)
{
	t_node *tmp;

	if (!*set || !node)
		return (0);
	tmp = *set;
	while (tmp)
	{
		if (compare_nodes(tmp, node))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
** Add given node to given set
*/

void	add_node(t_node **set, t_node *node)
{
	if (!node || !set)
		return ;
	node->next = *set;
	*set = node;
}

/*
** Remove given node from given set
*/

void	rm_node(t_node **set, t_node *node)
{
	t_node *tmp;
	t_node *ph;

	if (!*set || !node)
		return ;
	tmp = *set;
	if (compare_nodes(tmp, node))
	{
		*set = tmp->next;
		tmp->next = NULL;
		return ;
	}
	while (tmp->next)
	{
		ph = tmp->next;
		if (compare_nodes(ph, node))
		{
			tmp->next = ph->next;
			ph->next = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}
