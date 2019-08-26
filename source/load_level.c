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
		if (ft_strequ(info[0], "map_height:"))
			LEVEL->height = ft_atoi(info[1]);
		if (ft_strequ(info[0], "map_width:"))
			LEVEL->width = ft_atoi(info[1]);
		if (ft_strequ(info[0], "player_pos:"))
			PLAYER->pos = (t_dpoint){ft_atoi(info[1]) + 0.5, ft_atoi(info[2]) + 0.5};
		if (ft_strequ(info[0], "player_dir:"))
			PLAYER->angle = (double)ft_atoi(info[1]);
		if (ft_strequ(info[0], "object_count:"))
			LEVEL->object_count = ft_atoi(info[1]);
		ft_free_2darray((void**)info);
		free(line);
	}
	free(line);
	return (fd);
}

void				init_level(t_mlx *mlx, char *file)
{
	int		fd;
	int		i;
	int		j;
	char	*line;
	char	**tab;

	j = 0;
	LEVEL = MEM(t_level);
	PLAYER = MEM(t_player);
	fd = get_level_info(mlx, file);
	MAP = (int**)ft_memalloc(sizeof(int*) * LEVEL->height);
	while (ft_get_next_line(fd, &line))
	{
		i = 0;
		MAP[j] = (int*)ft_memalloc(sizeof(int) * LEVEL->width);
		tab = ft_strsplit(line, ' ');
		while (tab[i])
		{
			MAP[j][i] = ft_atoi(tab[i]);
			i++;
		}
		ft_free_2darray((void**)tab);
		free(line);
		j++;
	}
	set_player_angle(PLAYER, PLAYER->angle);
	close(fd);
}
