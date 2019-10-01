/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gun.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:14 by fhignett       #+#    #+#                */
/*   Updated: 2019/10/01 15:22:51 by flintlouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			death_animation(t_mlx *mlx, long ms)
{
	int i;

	i = LEVEL->enemy_count - 1;
	while (i >= 0)
	{
		ENEMIES[i].ss->ms += ENEMIES[i].ss->ms < 200 ? ms : 0;
		if (ENEMIES[i].ss->hit && ENEMIES[i].ss->ms > 120
		&& ENEMIES[i].ss->hit < ENEMY_DEAD)
		{
			ENEMIES[i].ss->sprite = TEXTURES[ENEMIES[i].ss->hit];
			ENEMIES[i].ss->hit++;
			ENEMIES[i].ss->ms = 0;
		}
		i--;
	}
}

static void			enemy_hit(t_mlx *mlx, int *fired)
{
	int i;
	int mid;

	mid = WIDTH >> 1;
	i = LEVEL->enemy_count - 1;
	if (*fired == 1)
	{
		while (i >= 0)
		{
			if (!ENEMIES[i].ss->hit &&
				(ENEMIES[i].ss->rel_loc.x >= -0.3
				&& ENEMIES[i].ss->rel_loc.x <= 0.3)
				&& mlx->z[mid] > ENEMIES[i].ss->rel_loc.y)
			{
				ENEMIES[i].ss->hit = ENEMY;
				break ;
			}
			i--;
		}
	}
}

static void			draw_gun(t_mlx *mlx, t_texture *gun, int size)
{
	int		x;
	int		y;
	t_point	draw;
	t_point start;
	t_point txtr;

	draw.x = gun->width * size;
	draw.y = gun->height * size;
	start.x = (WIDTH >> 1) - (draw.x >> 1);
	start.y = HEIGHT - draw.y;
	x = 0;
	while (x < draw.x)
	{
		txtr.x = (gun->width / (double)draw.x) * x;
		y = 0;
		while (y < draw.x)
		{
			txtr.y = (gun->height / (double)draw.y) * y;
			if (gun->colours[txtr.y][txtr.x].opacity > 0)
				put_pixel(start.x + x, start.y + y,
				mlx, gun->colours[txtr.y][txtr.x]);
			y++;
		}
		x++;
	}
}

static void			fired_frames(long *frames, int *fired,
t_controls *controls, long ms)
{
	*frames += *frames < 200 ? ms : 0;
	*fired += controls->shoot ? 1 : 0;
	if (*fired > 1 && !controls->shoot)
		*fired = 0;
}

void				fire_gun(t_mlx *mlx, t_texture *gun, int size, long ms)
{
	static int	i;
	static int	fired;
	static long	frames;

	fired_frames(&frames, &fired, CONTROLS, ms);
	death_animation(mlx, ms);
	if ((CONTROLS->shoot && i == 0) || (i > 0 && i < 6))
	{
		if (frames >= 20)
		{
			draw_gun(mlx, &gun[i], size);
			i++;
			frames = 0;
		}
		else
			draw_gun(mlx, &gun[i], size);
		enemy_hit(mlx, &fired);
	}
	else
	{
		if (i == 6 && !CONTROLS->shoot)
			i = 0;
		draw_gun(mlx, &gun[0], size);
	}
}
