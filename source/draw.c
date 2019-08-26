#include "wolf3d.h"

static void	shift_colour(t_colour *c, int nb)
{
	c->r >>= nb;
	c->g >>= nb;
	c->b >>= nb;
}

void		put_pixel(int x, int y, t_mlx *mlx, t_colour colour)
{
	int i;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * mlx->bits_per_pixel / 8) + (y * mlx->size_line);
		mlx->data_addr[i] = colour.b;
		i++;
		mlx->data_addr[i] = colour.g;
		i++;
		mlx->data_addr[i] = colour.r;
	}
}

void	draw_texture(t_mlx *mlx, t_texture *texture, int x, t_draw draw)
{
	int y;
	int pixel_y;
	long d; /* Goes beyond an integer */
	t_colour **colours = texture->colours;
	t_colour colour;

	y = draw.start;
	while (y < draw.end)
	{
		d = (y << 8) - ((HEIGHT - (long)draw.height) << 7); //y * 256 - HEIGHT * 128 + (long)wall_height * 128 (Voor afronding fouten)
		pixel_y = ((d * texture->height) / draw.height) >> 8; // / 256
		colour = colours[pixel_y][draw.x];
		if (draw.side == 1)
			shift_colour(&colour, 1);
		put_pixel(x, y, mlx, colour);
		y++;
	}
}

void	draw_sprite(t_mlx *mlx, t_texture *texture, int x, t_draw draw)
{
	int y;
	int texture_y;
	long d;
	t_colour **colours = texture->colours;
	t_colour colour;
	
	y = draw.start;
	while (y < draw.end)
	{
		d = (y << 8) - ((HEIGHT - (long)draw.height) << 7);
		texture_y = ((d * texture->height) / draw.height) >> 8;
		colour = colours[texture_y][draw.x];
		if (colour.opacity > 0)
			put_pixel(x, y, mlx, colour);
		y++;
	}
}