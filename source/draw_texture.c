#include "wolf3d.h"

void	shift_colour(t_colour *c, int nb)
{
	c->r >>= nb;
	c->g >>= nb;
	c->b >>= nb;
}

void	draw_texture(t_mlx *mlx, int *draw_pos, int wall_height, int textureId, int side, int x, int texture_x)
{
	int y;
	int texture_y;
	long d; /* Goes beyond an integer */

	t_texture texture = TEXTURES[textureId];
	t_colour **colours = texture.colours;
	t_colour colour;
	y = draw_pos[0];
	while (y < draw_pos[1])
	{
		d = (y << 8) - ((HEIGHT - (long)wall_height) << 7); //y * 256 - HEIGHT * 128 + (long)wall_height * 128 (Voor afronding fouten)
		texture_y = ((d * texture.height) / wall_height) >> 8; // / 256
		colour = colours[texture_y][texture_x];
		if (side == 1)
			shift_colour(&colour, 1);
		// if (colours[texture_y][texture_x].opacity > 0)
			put_pixel(x, y, mlx, colours[texture_y][texture_x]);
		y++;
	}
}

void	draw_sprite(t_mlx *mlx, int *draw_pos, int wall_height, t_texture *texture, int x, int texture_x)
{
	int y;
	int texture_y;
	long d; /* Goes beyond an integer */

	t_colour **colours = texture->colours;
	y = draw_pos[0];
	while (y < draw_pos[1])
	{
		d = (y << 8) - ((HEIGHT - (long)wall_height) << 7); //y * 256 - HEIGHT * 128 + (long)wall_height * 128 (Voor afronding fouten)
		texture_y = ((d * texture->height) / wall_height) >> 8; // / 256
		if (colours[texture_y][texture_x].opacity > 0)
			put_pixel(x, y, mlx, colours[texture_y][texture_x]);
		y++;
	}
}