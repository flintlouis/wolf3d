#include "wolf3d.h"

void gun(t_mlx *mlx, t_texture *gun, int size)
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
		text_x = (gun->width / draw_width) * x;
		y = 0;
		while (y < draw_height)
		{
			text_y = (gun->height / draw_height) * y;
			if (gun->colours[text_y][text_x].opacity > 0)
			// if (gun->colours[y][x].opacity > 0)
				put_pixel(startx + x, starty + y, mlx, /* (t_colour){255,0,0} */gun->colours[text_y][text_x]);
				// put_pixel(startx + x, starty + y, mlx, /* (t_colour){255,0,0} */gun->colours[y][x]);
			y++;
		}
		x++;
	}
}