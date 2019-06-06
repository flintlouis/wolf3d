#include "wolf3d.h"

void            put_pixel(int x, int y, t_mlx *mlx, t_colour colour)
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

/*
** X++
*/

static  void    plot_line1(t_mlx *mlx, t_point a, t_point b)
{
	int	delta_y;
	int	delta_x;
	int	d;
	int	sy;

	delta_x = b.x - a.x;
	delta_y = b.y - a.y;
	d = 2 * delta_y - delta_x;
	sy = delta_y >= 0 ? 1 : -1;
	delta_y = ABS(delta_y);
	while (a.x <= b.x)
	{
		put_pixel(a.x, a.y, mlx, (t_colour){0xff, 0xff, 0xff});
		if (d > 0)
		{
			a.y += sy;
			d -= 2 * delta_x;
		}
		d += 2 * delta_y;
		a.x++;
    }
}

/*
** Y++
*/

static  void    plot_line2(t_mlx *mlx, t_point a, t_point b)
{
	int	delta_x;
	int	delta_y;
	int	d;
	int	sx;

	delta_x = b.x - a.x;
	delta_y = b.y - a.y;
	d = 2 * delta_x - delta_y;
	sx = delta_x >= 0 ? 1 : -1;
	delta_x = ABS(delta_x);
	while (a.y <= b.y)
	{
		put_pixel(a.x, a.y, mlx, (t_colour){0xff, 0xff, 0xff});
		if (d > 0)
		{
			a.x += sx;
			d -= 2 * delta_y;
		}
		d += 2 * delta_x;
		a.y++;
	}
}

/*
** Makes sure with the first 'if' statements which delta is bigger
** between x and y and with the second 'if' statements it checks
** that the delta between a & b never a negative number is
*/

static  void    draw_line(t_mlx *mlx, t_point a, t_point b)
{
	int dx;
	int dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (ABS(dx) >= ABS(dy))
	{
		if (dx > 0)
			plot_line1(mlx, a, b);
		else
			plot_line1(mlx, b, a);
	}
	else
	{
		if (dy > 0)
			plot_line2(mlx, a, b);
		else
			plot_line2(mlx, b, a);
	}
}
