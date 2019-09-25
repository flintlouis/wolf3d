/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_level.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:31 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/25 11:44:37 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int		get_level_info(t_mlx *mlx, char *file)
{
	int		fd;
	char	*line;
	char	**info;

	fd = open(file, O_RDONLY);
	while (ft_get_next_line(fd, &line))
	{
		if (ft_strequ(line, ""))
			break ;
		info = ft_strsplit(line, ' ');
		if (ft_strequ(info[0], "level_size:"))
			LEVEL->size = (t_point){ft_atoi(info[1]), ft_atoi(info[2])};
		if (ft_strequ(info[0], "player_pos:"))
		{
			PLAYER->pos =
			(t_dpoint){ft_atoi(info[1]) + 0.5, ft_atoi(info[2]) + 0.5};
		}
		if (ft_strequ(info[0], "player_dir:"))
			PLAYER->angle = (double)ft_atoi(info[1]);
		ft_free_2darray((void**)info);
		free(line);
	}
	free(line);
	return (fd);
}

static void		free_something(char *line, char **tab)
{
	ft_free_2darray((void**)tab);
	free(line);
}

void			init_level(t_mlx *mlx, char *file)
{
	int		fd;
	int		i;
	int		j;
	char	*line;
	char	**tab;

	fd = get_level_info(mlx, file);
	MAP = (int**)ft_memalloc(sizeof(int*) * LEVEL->size.y);
	j = 0;
	while (ft_get_next_line(fd, &line))
	{
		i = 0;
		MAP[j] = (int*)ft_memalloc(sizeof(int) * LEVEL->size.x);
		tab = ft_strsplit(line, ' ');
		while (tab[i])
		{
			MAP[j][i] = ft_atoi(tab[i]);
			LEVEL->object_count += MAP[j][i] > WALLCOUNT ? 1 : 0;
			LEVEL->enemy_count += MAP[j][i] == ENEMY ? 1 : 0;
			i++;
		}
		free_something(line, tab);
		j++;
	}
	close(fd);
}
