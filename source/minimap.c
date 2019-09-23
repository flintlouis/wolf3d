/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:52:19 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/23 12:41:30 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdlib.h>

static int		angle_moved(t_player *player)
{
	static int prev_angle;

	if (prev_angle < (int)player->angle - 80
	|| prev_angle > (int)player->angle + 80)
	{
		prev_angle = (int)player->angle;
		return (1);
	}
	return (0);
}

void			mini_map(t_player *player, int **map)
{
	int i;
	int j;
	static int prev_pos_x;
	static int prev_pos_y;

	i = 0;
	j = 0;
	if (prev_pos_x != (int)player->pos.x || prev_pos_y != (int)player->pos.y
	|| angle_moved(player))
	{
		system("clear");
		prev_pos_y = player->pos.y;
		prev_pos_x = player->pos.x;
		while (j < 24)
		{
			while (i < 24)
			{
				if (j == (int)player->pos.y && i == (int)player->pos.x)
				{
					if (player->angle >= 135 && player->angle < 225)
						ft_putstr("^ ");
					else if (player->angle >= 225 && player->angle < 315)
						ft_putstr("> ");
					else if (player->angle >= 45 && player->angle < 135)
						ft_putstr("< ");
					else
						ft_putstr("v ");
				}
				else if (!map[j][i] || map[j][i] > WALLCOUNT)
					ft_putstr("  ");
				else
					ft_putstr("[]");
				i++;
			}
			ft_putendl("");
			j++;
			i = 0;
		}
	}
}
