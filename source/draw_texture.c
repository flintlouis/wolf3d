#include "wolf3d.h"

void		put_pixel(int x, int y, t_mlx *mlx, t_colour colour);

t_colour	divide_colour(t_colour c, int nb)
{
	c.r /= nb;
	c.g /= nb;
	c.b /= nb;
	return (c);
}

void	draw_texture(t_mlx *mlx, t_point a, t_point b, int id)
{
	int i;
	int j;
	int height;
	int width;

	i = 0;
	j = 0;
	height = ABS(b.y - a.y);
	id--;
	while (a.y <= b.y)
	{
		put_pixel(a.x, a.y, mlx, TEXTURES[id].colours[i][j]);
		a.y++;
		i++;
	}

}

// void	draw_texture(t_mlx *mlx)
// {
// 	int nb;
// 	int j, i = 0;
// 	int id = 9;

// 	id--;
// 	while (i < TEXTURES->height) {
// 		j = 0;
// 		while (j < TEXTURES->width) {

// 			nb = 1;
// 			put_pixel(10 + j, 10 + i, mlx, divide_colour(TEXTURES[id].colours[i][j], nb));
// 			nb++;
// 			put_pixel(100 + j, 10 + i, mlx, divide_colour(TEXTURES[id].colours[i][j], nb));
// 			nb++;
// 			put_pixel(200 + j, 10 + i, mlx, divide_colour(TEXTURES[id].colours[i][j], nb));
// 			nb++;
// 			put_pixel(300 + j, 10 + i, mlx, divide_colour(TEXTURES[id].colours[i][j], nb));
// 			j++;
// 		}
// 		i++;
// 	}
// }