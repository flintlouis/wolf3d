#include "wolf3d.h"
#include "mlx.h"
#include <stdlib.h> /* FOR MINIMAP */
#include <pthread.h>

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
	char *fps;

	fps = ft_itoa(frames());
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_string_put(mlx->mlx, mlx->win, 10, 10, 0xffffff, fps);
	free(fps);
	ft_bzero(mlx->data_addr, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
}

static void	join_threads(int i, pthread_t *threads)
{
	while (i >= 0)
	{
		i--;
		pthread_join(threads[i], NULL);
	}
}

static void threading(t_mlx *mlx)
{
	int			i;
	t_mlx		data[THREAD];
	pthread_t	threads[THREAD];

	i = 0;
	while (i < THREAD)
	{
		ft_memcpy(&data[i], mlx, sizeof(t_mlx));
		data[i].x[0] = (WIDTH / THREAD) * i;
		data[i].x[1] = (WIDTH / THREAD) * (i + 1);
		pthread_create(&threads[i], NULL, raycaster, &data[i]);
		i++;
	}
	join_threads(i, threads);
}

void	draw_texture_test(t_mlx *mlx)
{
	int nb;
	int j, i = 0;
	int id = 10;
	t_colour colour;

	id--;
	while (i < TEXTURES[id].height) {
		j = 0;
		while (j < TEXTURES[id].width) {
			colour = TEXTURES[id].colours[i][j];
			if (TEXTURES[id].colours[i][j].opacity)
				put_pixel(10 + j, 10 + i, mlx, colour);
			colour = TEXTURES[id - 1].colours[i][j];
			if (TEXTURES[id - 1].colours[i][j].opacity)
				put_pixel(300 + j, 10 + i, mlx, colour);
			j++;
		}
		i++;
	}
}

int wolfenstein(t_mlx *mlx)
{
	draw_image(mlx);
	threading(mlx);

	// draw_texture_test(mlx);

	move_player(mlx);
	player_look(mlx);
	// mini_map(mlx->player, MAP);
	return (0);
}
