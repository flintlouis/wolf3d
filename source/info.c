/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 15:55:03 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/25 16:34:27 by fhignett      ########   odam.nl         */
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

void			info(t_mlx *mlx)
{
	write_info(mlx, "HEALTH", PLAYER->health, 0);
	if (!PLAYER->health)
		mlx_string_put(mlx->mlx, mlx->win, WIDTH >> 1, HEIGHT >> 1,
		0xff0000, "DEAD");
}
