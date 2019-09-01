#include "wolf3d.h"

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

	/* USE TIME BETWEEN FRAMES */
	ms += time_between_frames();
	if ((CONTROLS->shoot && i < 6) || (i > 0 && i < 6))
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