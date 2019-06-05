#include "wolf3d.h"
#include <fcntl.h>
#include <stdlib.h>

t_map	*get_map(char *file)
{
	t_map *map;
	char *line;
	int fd;

	fd = open(file, O_RDONLY);
	map = MEM(t_map);
	ft_get_next_line(fd, &line);
	return (map);
}