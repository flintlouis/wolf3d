#include "wolf3d.h"

t_colour	divide_colour(t_colour c, int nb)
{
	c.r /= nb;
	c.g /= nb;
	c.b /= nb;
	return (c);
}

void	draw_texture(t_mlx *mlx, int *draw_pos, int wall_height, int texture, int side, int x, int texture_x)
{
	int y;
	int texture_y;
	int d;

	y = draw_pos[0];
	while (y < draw_pos[1])
	{
		d = y * 256 - HEIGHT * 128 + wall_height * 128;
		texture_y = ((d * TEXTURES->height) / wall_height) / 256;
		t_colour colour = TEXTURES[texture].colours[texture_y][texture_x];
		if (side ==1)
			colour = divide_colour(colour, 2);
		put_pixel(x, y, mlx, colour);
		y++;
	}
}