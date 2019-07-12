#include "wolf3d.h"

void		put_pixel(int x, int y, t_mlx *mlx, t_colour colour);

void	draw_texture(t_mlx *mlx, t_point a, t_point b, int id)
{
	int i;
	int j;

	i = 0;
	j = 0;
	id--;
	while (a.y <= b.y)
	{
		put_pixel(a.x, a.y, mlx, TEXTURES[id].colours[i][j]);
		a.y++;
		i++;
	}

}