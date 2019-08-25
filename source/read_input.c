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

static void		get_map_size(char *file, int *height, int *width)
{
	char *line;
	int fd;
	int size;

	size = 0;
	fd = open(file, O_RDONLY);
	while (ft_get_next_line(fd, &line))
	{
		size = get_map_width(line);
		if (!*width)
			*width = size;
		/* else if (width != map->width) ALS WE WILLEN DAT DE WIDTH OVERAL GELIJK MOET ZIJN
			NOT A SQUARE */
		(*height)++;
		free(line);
	}
	close(fd);
}

int				**get_map(char *file, int *map_height, int *map_width, int *object_count)
{
	int **map;
	int fd;
	char *line;
	int i;
	int j;
	char **tab;

	i = 0;
	j = 0;
	*map_height = 0; //////////////
	*map_width = 0; //////////////
	*object_count = 0; //////////////
	get_map_size(file, map_height, map_width);
	fd = open(file, O_RDONLY);
	map = (int**)ft_memalloc(sizeof(int*) * *map_height);
	while (ft_get_next_line(fd, &line))
	{
		map[j] = (int*)ft_memalloc(sizeof(int) * *map_width);
		tab = ft_strsplit(line, ' ');
		while (tab[i])
		{
			map[j][i] = ft_atoi(tab[i]);
			*object_count += map[j][i] > 5 ? 1 : 0;
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
