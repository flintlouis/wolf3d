#include "wolf3d.h"
#include "mlx.h"
#include <stdlib.h> /* FOR MINIMAP */

static void		mini_map(t_player *player, int **map)
{
	static int prev_pos_x;
	static int prev_pos_y;
	
	if (prev_pos_x != (int)player->pos.x || prev_pos_y != (int)player->pos.y)
	{
		system("clear");
		prev_pos_y = player->pos.y;
		prev_pos_x = player->pos.x;
		int i = 0;
		int j = 0;
		while (j < 24)
		{
			while (i < 24)
			{
				if (j == (int)player->pos.y && i == (int)player->pos.x)
					ft_printf("X ");
				else
					ft_printf("%d ", map[j][i]);
				i++;
			}
			ft_putendl("");
			j++;
			i = 0;

		}
	}
}

static void		draw_image(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_bzero(mlx->data_addr, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
}

int wolfenstein(t_mlx *mlx)
{
	static double x;
	static double y;

	if (x != PLAYER->pos.x || y != PLAYER->pos.y) {
		system("clear");
		ft_printf("player: posx = %.2f, posy = %.2f\n", PLAYER->pos.x, PLAYER->pos.y);
		x = PLAYER->pos.x;
		y = PLAYER->pos.y;
	}

	raycaster(mlx);
	draw_image(mlx);

	move_player(mlx);
	player_look(mlx);

	// mini_map(mlx->player, MAP);
	return (0);
}