#include "wolf3d.h"
#include <fcntl.h>
#include <unistd.h>

t_texture	*load_textures(void)
{
	ssize_t		fd[TEXTURE_COUNT];
	t_texture	*textures;
	int 		i;

	fd[0] = open("img/RED.bmp", O_RDONLY);
	fd[1] = open("img/BLk.bmp", O_RDONLY);
	fd[2] = open("img/WHT.bmp", O_RDONLY);
	textures = (t_texture*)ft_memalloc(sizeof(t_texture) * TEXTURE_COUNT);
	i = 0;
	while (i < TEXTURE_COUNT){
		textures[i] = store_texture(fd[i]);
		i++;
	}
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
	texture.width = (int)header[18]; //*(int*)&header[18];
	texture.height = (int)header[22];
	texture.colours = (t_colour**)ft_memalloc(sizeof(t_colour*) * texture.height);
	i = 0;
	while (i < texture.height){
		j = 0;
		texture.colours[i] = (t_colour*)ft_memalloc(sizeof(t_colour) * texture.width);
		while (j < texture.width)
		{
			read(fd, buff, 3);
			if (buff[0]) {
				texture.colours[i][j].b = buff[0];
				texture.colours[i][j].g = buff[1];
				texture.colours[i][j].r = buff[2];
			}
			j++;
		}
		i++;
	}
	return (texture);
}
