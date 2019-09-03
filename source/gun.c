#include "wolf3d.h"

void	enemy_hit(t_mlx *mlx, int *fired)
{
	int i;
	static 
	int mid;
	long frames;


	frames = time_between_frames();
	mid = WIDTH >> 1;
	i = LEVEL->enemy_count - 1;
	if (*fired == 1)
	{
		while (i >= 0)
		{
			if (!ENEMIES[i]->hit &&
				(ENEMIES[i]->rel_loc.x >= -0.2 && ENEMIES[i]->rel_loc.x <= 0.2)
				&& mlx->z[mid] > ENEMIES[i]->rel_loc.y)
			{
				ENEMIES[i]->hit = 14;
				break ;
			}
			i--;
		}
	}
	i = LEVEL->enemy_count - 1;
	while (i >= 0)
	{
		ENEMIES[i]->ms += ENEMIES[i]->ms < 200 ? frames : 0;
		if (ENEMIES[i]->hit && ENEMIES[i]->ms > 100 && ENEMIES[i]->hit < 19)
		{
			ENEMIES[i]->sprite = TEXTURES[ENEMIES[i]->hit];
			ENEMIES[i]->hit++;
			ENEMIES[i]->ms = 0;
		}
	i--;
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
	static int i;
	static long ms;
	static int fired;

	fired += CONTROLS->shoot ? 1 : 0;
	if (fired > 1 && !CONTROLS->shoot)
		fired = 0;
	ms += ms < 200 ? time_between_frames() : 0;
	enemy_hit(mlx, &fired);
	if ((CONTROLS->shoot && i == 0) || (i > 0 && i < 6))
	{
		if (ms >= 20)
		{
			draw_gun(mlx, &gun[i], size);
			i++;
			ms = 0;
		} else
			draw_gun(mlx, &gun[i], size);
	}
	else
	{
		if (i == 6 && !CONTROLS->shoot)
			i = 0;
		draw_gun(mlx, &gun[0], size);
	}
	for (int aim = -10; aim <= 10; aim++)
	{
		if (aim < -3 || aim > 3)
		{
			put_pixel((WIDTH>>1) + aim, HEIGHT>>1, mlx, (t_colour){255,255,0});
			put_pixel(WIDTH>>1, (HEIGHT>>1) + aim, mlx, (t_colour){255,255,0});
		}
		put_pixel(WIDTH>>1, HEIGHT>>1, mlx, (t_colour){255,0,0});
	}
}