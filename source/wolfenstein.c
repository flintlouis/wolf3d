#include "wolf3d.h"
#include "mlx.h"

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
				{
					if (player->angle >= 135 && player->angle < 225)
						ft_putstr("^ ");
					else if (player->angle >= 225 && player->angle < 315)
						ft_putstr("> ");
					else if (player->angle >= 45 && player->angle < 135)
						ft_putstr("< ");
					else
						ft_putstr("v ");
				}
				else if (!map[j][i])
					ft_putstr("  ");
				else if (map[j][i] > WALLCOUNT)
					ft_putstr("S ");
				else
					ft_putstr("W ");
				i++;
			}
			ft_putendl("");
			j++;
			i = 0;
		}
	}
}

static void write_info(t_mlx *mlx, char *label, int value1, int value2, int line)
{
	int y_pos = 10 + 20 * line;
	char *ch_val1;
	char *ch_val2;

	ch_val1 = ft_itoa(value1);
	ch_val2 = ft_itoa(value2);
	
	mlx_string_put(mlx->mlx, mlx->win, 10, y_pos, 0xffffff, label);
	mlx_string_put(mlx->mlx, mlx->win, 200, y_pos, 0xffffff, ch_val1);
	mlx_string_put(mlx->mlx, mlx->win, 250, y_pos, 0xffffff, ch_val2);
	free(ch_val1);
	free(ch_val2);
}

static void		info(t_mlx *mlx)
{
	write_info(mlx, "FPS", 0, frames(), 0);
	write_info(mlx, "Player pos x,y", PLAYER->pos.x, PLAYER->pos.y, 1);
	write_info(mlx, "Plane x,y", PLAYER->plane.x*100, PLAYER->plane.y*100, 2);
	write_info(mlx, "Looking dir x,y", PLAYER->looking_dir.x*100, PLAYER->looking_dir.y*100, 3);
	write_info(mlx, "Angle", 0, PLAYER->angle, 4);
}

static void		draw_image(t_mlx *mlx)
{
	int i;
	int *data;
	int size;

	i = 0;

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	size = HEIGHT * WIDTH;
	data = (int*)mlx->data_addr;
	while (i < (size >> 1))
	{
		data[i] = 0x000000;
		i++;
	}
	while (i < size)
	{
		data[i] = 0x1F1F1F;
		i++;
	}
	info(mlx);
}

void	join_threads(int i, pthread_t *threads)
{
	while (i >= 0)
	{
		i--;
		pthread_join(threads[i], NULL);
	}
}

static void threading(t_mlx *mlx, void*(*f)(void*))
{
	int			i;
	t_mlx		data[THREAD];
	pthread_t	threads[THREAD];

	i = 0;
	while (i < THREAD)
	{
		ft_memcpy(&data[i], mlx, sizeof(t_mlx));
		data[i].x[0] = (WIDTH / THREAD) * i;
		data[i].x[1] = i == THREAD - 1 ? WIDTH : (WIDTH / THREAD) * (i + 1);
		pthread_create(&threads[i], NULL, f, &data[i]);
		i++;
	}
	join_threads(i, threads);
}

void move_enemy(t_mlx *mlx);

int wolfenstein(t_mlx *mlx)
{
	long ms;
	static long frames;

	ms = time_between_frames();
	frames += frames < 5000 ? ms : 0;
	threading(mlx, raycaster);
	spritecaster(mlx);
	fire_gun(mlx, GUN, 12, ms);
	draw_image(mlx);
	move_player(mlx);
	player_look(PLAYER, CONTROLS);

	if (frames >= 60) {
		move_enemy(mlx);
		frames = 0;
	}

	// mini_map(PLAYER, MAP);
	return (0);
}
