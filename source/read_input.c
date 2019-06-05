#include "wolf3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int		get_map_width(char *line)
{
	int width;
	char **tab;
	int i;

	i = 0;
	width = 0;
	tab = ft_strsplit(line, ' ');
	while (tab[i])
	{
		i++;
		width++;
	}
	ft_free_2darray((void**)tab);
	return (width);
}

static void		get_map_size(char *file, t_map *map)
{
	char *line;
	int fd;
	int width;

	width = 0;
	fd = open(file, O_RDONLY);
	while (ft_get_next_line(fd, &line))
	{
		width = get_map_width(line);
		if (!map->width)
			map->width = width;
		/* else if (width != map->width) ALS WE WILLEN DAT DE WIDTH OVERAL GELIJK MOET ZIJN
			NOT A SQUARE */
		map->height++;
		free(line);
	}
	close(fd);
}

t_map	*get_map(char *file)
{
	t_map *map;
	int fd;
	char *line;
	int i;
	int j;
	char **tab;

	i = 0;
	j = 0;
	map = MEM(t_map);
	get_map_size(file, map);
	fd = open(file, O_RDONLY);
	map->map = (int**)ft_memalloc(sizeof(int*) * map->height);
	while (ft_get_next_line(fd, &line))
	{
		map->map[j] = (int*)ft_memalloc(sizeof(int) * map->width);
		tab = ft_strsplit(line, ' ');
		while (tab[i])
		{
			map->map[j][i] = ft_atoi(tab[i]);
			i++;
		}
		ft_free_2darray((void**)tab);
		free(line);
		j++;
		i = 0;
	}
	close(fd);
	return (map);
}
