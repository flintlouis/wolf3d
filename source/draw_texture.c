#include "wolf3d.h"

void		put_pixel(int x, int y, t_mlx *mlx, t_colour colour);

void	draw_texture(t_mlx *mlx)
{
	t_point begin = (t_point){10, 10};
	int j, i = 0;

	while (i < TEXTURES->height) {
		j = 0;
		while (j < TEXTURES->width) {
			put_pixel(begin.x + j, begin.y + i, mlx, mlx->textures[0].colours[i][j]);
			j++;
		}
		i++;
	}
}