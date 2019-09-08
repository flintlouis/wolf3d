#include "wolf3d.h"

static void death_animation(t_mlx *mlx, long ms)
{
	int i;

	i = LEVEL->enemy_count - 1;
	while (i >= 0)
	{
		ENEMIES[i].ss->ms += ENEMIES[i].ss->ms < 200 ? ms : 0;
		if (ENEMIES[i].ss->hit && ENEMIES[i].ss->ms > 120 && ENEMIES[i].ss->hit < 19)
		{
			ENEMIES[i].ss->sprite = TEXTURES[ENEMIES[i].ss->hit];
			ENEMIES[i].ss->hit++;
			ENEMIES[i].ss->ms = 0;
		}
	i--;
	}
}

static void	enemy_hit(t_mlx *mlx, int *fired)
{
	int i;
	static 
	int mid;

	mid = WIDTH >> 1;
	i = LEVEL->enemy_count - 1;
	if (*fired == 1)
	{
		while (i >= 0)
		{
			if (!ENEMIES[i].ss->hit &&
				(ENEMIES[i].ss->rel_loc.x >= -0.2 && ENEMIES[i].ss->rel_loc.x <= 0.2)
				&& mlx->z[mid] > ENEMIES[i].ss->rel_loc.y)
			{
				ENEMIES[i].ss->hit = 14;
				break ;
			}
			i--;
		}
	}
}

static void draw_gun(t_mlx *mlx, t_texture *gun, int size)
{
	int x;
	int y;
	int startx;
	int starty;
	int draw_width;
	int draw_height;
	int text_x;
	int text_y;

	draw_width = gun->width * size;
	draw_height = gun->height * size;
	startx = (WIDTH >> 1) - (draw_width >> 1);
	starty = HEIGHT - draw_height;
	x = 0;
	while (x < draw_width)
	{
		text_x = (gun->width / (double)draw_width) * x;
		y = 0;
		while (y < draw_height)
		{
			text_y = (gun->height / (double)draw_height) * y;
			if (gun->colours[text_y][text_x].opacity > 0)
				put_pixel(startx + x, starty + y, mlx, gun->colours[text_y][text_x]);
			y++;
		}
		x++;
	}
}

void fire_gun(t_mlx *mlx, t_texture *gun, int size)
{
	long ms;
	static int i;
	static long frames;
	static int fired;

	ms = time_between_frames();
	frames += frames < 200 ? ms : 0;
	death_animation(mlx, ms);
	fired += CONTROLS->shoot ? 1 : 0;
	if (fired > 1 && !CONTROLS->shoot)
		fired = 0;
	if ((CONTROLS->shoot && i == 0) || (i > 0 && i < 6))
	{
		if (frames >= 20)
		{
			draw_gun(mlx, &gun[i], size);
			i++;
			frames = 0;
		} else
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