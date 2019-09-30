/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_level.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:31 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/30 18:17:52 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int		get_level_info(t_level *level, t_player *player, char *file)
{
	int		fd;
	char	*line;
	char	**info;

	fd = open(file, O_RDONLY);
	fd_error(fd);
	while (ft_get_next_line(fd, &line))
	{
		if (ft_strequ(line, ""))
			break ;
		info = ft_strsplit(line, ' ');
		if (ft_strequ(info[0], "level_size:"))
			level->size = (t_point){ft_atoi(info[1]), ft_atoi(info[2])};
		if (ft_strequ(info[0], "player_pos:"))
			player->pos =
			(t_dpoint){ft_atoi(info[1]) + 0.5, ft_atoi(info[2]) + 0.5};
		if (ft_strequ(info[0], "player_dir:"))
			player->angle = (double)ft_atoi(info[1]);
		ft_free_2darray((void**)info);
		free(line);
	}
	free(line);
	info_error(level, player);
	return (fd);
}

static void		free_something(char *line, char **tab)
{
	ft_free_2darray((void**)tab);
	free(line);
}

static void		level(t_mlx *mlx, char **tab, int j, int *i)
{
	while (tab[*i])
	{
		size_error(*i, LEVEL->size.x, '>');
		MAP[j][*i] = ft_atoi(tab[*i]);
		if ((j == 0 || *i == 0 || j == LEVEL->size.y - 1 ||
		*i == LEVEL->size.x - 1) && !MAP[j][*i])
			MAP[j][*i] = 1;
		if (MAP[j][*i] > 0)
			spawn_error(*i, j, PLAYER->pos);
		LEVEL->object_count += MAP[j][*i] > WALLCOUNT ? 1 : 0;
		LEVEL->enemy_count += MAP[j][*i] == ENEMY ? 1 : 0;
		(*i)++;
	}
}

void			init_level(t_mlx *mlx, char *file)
{
	int		fd;
	int		i;
	int		j;
	char	*line;
	char	**tab;

	fd = get_level_info(LEVEL, PLAYER, file);
	MAP = (int**)ft_memalloc(sizeof(int*) * LEVEL->size.y);
	j = 0;
	while (ft_get_next_line(fd, &line))
	{
		size_error(j, LEVEL->size.y, '>');
		i = 0;
		MAP[j] = (int*)ft_memalloc(sizeof(int) * LEVEL->size.x);
		tab = ft_strsplit(line, ' ');
		level(mlx, tab, j, &i);
		free_something(line, tab);
		j++;
		size_error(i, LEVEL->size.x, '<');
	}
	size_error(j, LEVEL->size.y, '<');
	close(fd);
}
