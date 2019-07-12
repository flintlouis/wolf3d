#include "wolf3d.h"

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

void			draw_ver_line(t_mlx *mlx, t_point a, t_point b, t_colour colour)
{
	while (a.y <= b.y)
	{
		put_pixel(a.x, a.y, mlx, colour);
		a.y++;
	}
}
