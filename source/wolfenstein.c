/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wolfenstein.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:52:06 by fhignett       #+#    #+#                */
/*   Updated: 2019/10/04 17:42:44 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"

static void		draw_image(t_mlx *mlx)
{
	int i;
	int *data;
	int size;

	i = 0;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	size = HEIGHT * WIDTH;
	data = (int*)mlx->data_addr;
	while (i < (size >> 1))
	{
		data[i] = 0x000010;
		i++;
	}
	while (i < size)
	{
		data[i] = 0x1F1F1F;
		i++;
	}
}

void			join_threads(int i, pthread_t *threads)
{
	while (i >= 0)
	{
		i--;
		pthread_join(threads[i], NULL);
	}
}

static	void	threading(t_mlx *mlx, void *(*f)(void*))
{
	int			i;
	t_mlx		data[THREAD];
	pthread_t	threads[THREAD];

	i = 0;
	while (i < THREAD)
	{
		ft_memcpy(&data[i], mlx, sizeof(t_mlx));
		data[i].x[0] = (WIDTH / THREAD) * i;
		data[i].x[1] = i == THREAD - 1 ? WIDTH : (WIDTH / THREAD) * (i + 1);
		pthread_create(&threads[i], NULL, f, &data[i]);
		i++;
	}
	join_threads(i, threads);
}

int				wolfenstein(t_mlx *mlx)
{
	long		ms;
	static long	frames;

	if (PLAYER->health)
	{
		ms = time_between_frames();
		frames += frames < 5000 ? ms : 0;
		threading(mlx, raycaster);
		spritecaster(mlx);
		if (mlx->l != 3)
			fire_gun(mlx, GUN, 18, ms);
		draw_image(mlx);
		move_player(mlx);
		player_look(PLAYER, CONTROLS);
		if (frames >= 60)
		{
			move_enemy(mlx);
			frames = 0;
		}
		mini_map(PLAYER, LEVEL, MAP);
	}
	info(mlx);
	return (0);
}
