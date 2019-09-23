/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:08 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/23 12:12:42 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	shift_colour(t_colour *c, int nb)
{
	c->r >>= nb;
	c->g >>= nb;
	c->b >>= nb;
}

void		put_pixel(int x, int y, t_mlx *mlx, t_colour colour)
{
	int	*mem;
	int i;

	mem = (int*)mlx->data_addr;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = x + (y * mlx->size_line / 4);
		mem[i] = colour.b | (colour.g << 8) | (colour.r << 16);
	}
}

/*
** 'd' needs to be a long because it goes beyond an integer
** bitshift operators do the same as :
** y * 256 - HEIGHT * 128 + (long)wall_height * 128 (Voor afronding fouten)
*/

void		draw_object(t_mlx *mlx, t_texture *texture, int x, t_draw draw)
{
	int			y;
	int			pixel_y;
	long		d;
	t_colour	**colours;
	t_colour	colour;

	colours = texture->colours;
	y = draw.start;
	while (y < draw.end)
	{
		d = (y << 8) - ((HEIGHT - (long)draw.height) << 7);
		pixel_y = ((d * texture->height) / draw.height) >> 8;
		colour = colours[pixel_y][draw.x];
		if (draw.side == 1)
			shift_colour(&colour, 1);
		if (colour.opacity > 0)
			put_pixel(x, y, mlx, colour);
		y++;
	}
}
