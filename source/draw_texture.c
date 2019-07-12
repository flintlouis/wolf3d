#include "wolf3d.h"

void		put_pixel(int x, int y, t_mlx *mlx, t_colour colour);

void	draw_texture(t_mlx *mlx)
{
	t_point begin1 = (t_point){10, 10};
	t_point begin2 = (t_point){100, 10};
	t_point begin3 = (t_point){200, 10};
	t_point begin4 = (t_point){300, 10};
	t_point begin5 = (t_point){400, 10};
	t_point begin6 = (t_point){500, 10};
	t_point begin7 = (t_point){600, 10};
	t_point begin8 = (t_point){700, 10};
	t_point begin9 = (t_point){800, 10};
	t_point begin10 = (t_point){900, 10};
	int j, i = 0;

	while (i < TEXTURES->height) {
		j = 0;
		while (j < TEXTURES->width) {
			put_pixel(begin1.x + j, begin1.y + i, mlx, mlx->textures[0].colours[i][j]);
			put_pixel(begin2.x + j, begin2.y + i, mlx, mlx->textures[1].colours[i][j]);
			put_pixel(begin3.x + j, begin3.y + i, mlx, mlx->textures[2].colours[i][j]);
			put_pixel(begin4.x + j, begin4.y + i, mlx, mlx->textures[3].colours[i][j]);
			put_pixel(begin5.x + j, begin5.y + i, mlx, mlx->textures[4].colours[i][j]);
			put_pixel(begin6.x + j, begin6.y + i, mlx, mlx->textures[5].colours[i][j]);
			put_pixel(begin7.x + j, begin7.y + i, mlx, mlx->textures[6].colours[i][j]);
			put_pixel(begin8.x + j, begin8.y + i, mlx, mlx->textures[7].colours[i][j]);
			put_pixel(begin9.x + j, begin9.y + i, mlx, mlx->textures[8].colours[i][j]);
			put_pixel(begin10.x + j, begin10.y + i, mlx, mlx->textures[9].colours[i][j]);
			j++;
		}
		i++;
	}
}