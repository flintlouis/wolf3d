/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 15:55:03 by fhignett       #+#    #+#                */
/*   Updated: 2019/10/04 17:53:47 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"
#include <stdlib.h>

static	void	write_info(t_mlx *mlx, char *label, int value1, int line)
{
	int		y_pos;
	char	*ch_val1;

	y_pos = 10 + 20 * line;
	ch_val1 = ft_itoa(value1);
	mlx_string_put(mlx->mlx, mlx->win, 10, y_pos, 0xffffff, label);
	mlx_string_put(mlx->mlx, mlx->win, 200, y_pos, 0xffffff, ch_val1);
	free(ch_val1);
}

static int		no_more_enemies(t_enemy *enemies, t_level *level)
{
	int i;
	int dead;

	dead = 0;
	i = 0;
	while (i < level->enemy_count)
	{
		if (enemies[i].ss->hit)
			dead++;
		if (dead == level->enemy_count)
			return (1);
		i++;
	}
	return (0);
}

void			info(t_mlx *mlx)
{
	write_info(mlx, "HEALTH", PLAYER->health, 0);
	if (!PLAYER->health)
		mlx_string_put(mlx->mlx, mlx->win, WIDTH >> 1, HEIGHT >> 1,
		0xff0000, "DEAD");
	if (mlx->l == 2 && no_more_enemies(ENEMIES, LEVEL))
		mlx_string_put(mlx->mlx, mlx->win, WIDTH >> 1, HEIGHT >> 1,
		0xffff00, "RAMBO");
}
