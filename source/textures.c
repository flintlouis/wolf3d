#include "wolf3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int		get_textures_size(char *file)
{
	char *line;
	int fd;
	int size;

	size = 0;
	fd = open(file, O_RDONLY);
	while (ft_get_next_line(fd, &line))
	{
		size++;
		free(line);
	}
	close(fd);
	return (size);
}

static ssize_t		*get_textures_fd(int *size)
{
	int fd;
	ssize_t	*textures_fd;
	char *line;
	char *tmp;
	int i;

	i = 0;
	fd = open("source/textures.txt", O_RDONLY);
	*size = get_textures_size("source/textures.txt");
	textures_fd = (ssize_t*)ft_memalloc(sizeof(ssize_t) * (*size));
	while (ft_get_next_line(fd, &line))
	{
		tmp = line;
		line = ft_strjoin("img/", line);
		free(tmp);
		tmp = line;
		line = ft_strjoin(line, ".bmp");
		free(tmp);
		textures_fd[i] = open(line, O_RDONLY);
		free(line);
		i++;
	}
	close(fd);
	return (textures_fd);
}

t_texture	*load_textures(void)
{
	ssize_t		*textures_fd;
	t_texture	*textures;
	int 		i;
	int			size;

	textures_fd = get_textures_fd(&size);
	textures = (t_texture*)ft_memalloc(sizeof(t_texture) * size);
	i = 0;
	while (i < size){
		textures[i] = store_texture(textures_fd[i]);
		close(textures_fd[i]);
		i++;
	}
	free(textures_fd);
	return (textures);
}

t_texture	store_texture(ssize_t fd)
{
	t_texture		texture;
	t_byte			header[54];
	t_byte			buff[3];
	int 			i;
	int				j;

	/* read bitmap header */
	read(fd, header, 54);
	texture.width = *(int*)&header[18];
	texture.height = *(int*)&header[22];
	texture.colours = (t_colour**)ft_memalloc(sizeof(t_colour*) * texture.height);
	i = texture.height - 1;
	while (i >= 0){
		j = 0;
		texture.colours[i] = (t_colour*)ft_memalloc(sizeof(t_colour) * texture.width);
		while (j < texture.width)
		{
			read(fd, buff, 3);
			texture.colours[i][j].b = buff[0];
			texture.colours[i][j].g = buff[1];
			texture.colours[i][j].r = buff[2];
			j++;
		}
		i--;
	}
	return (texture);
}
