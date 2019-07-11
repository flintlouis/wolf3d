#include "wolf3d.h"
#include <fcntl.h>
#include <unistd.h>

t_texture	*load_textures(void)
{
	ssize_t		fd[TEXTURE_COUNT];
	t_texture	textures[TEXTURE_COUNT];
	int 		i;

	fd[0] = open("img/bluestone.bmp", O_RDONLY);
	fd[1] = open("img/bluestone.bmp", O_RDONLY);
	fd[2] = open("img/greystone.bmp", O_RDONLY);
	i = 0;
	while (i < TEXTURE_COUNT){
		textures[i] = store_texture(fd[i]);
		i++;
	}
	return (textures);
}

t_texture	store_texture(ssize_t fd)
{
	t_byte			header[54];
	t_texture		texture;
	t_byte			buff[3];
	int 			size;
	int 			i;

	/* read bitmap header */
	read(fd, header, 54);
	texture.width = *(int*)&header[18];
	texture.height = *(int*)&header[22];
	size = texture.width * texture.height;
	texture.colours = (t_colour*)ft_memalloc(sizeof(t_colour) * size);
	i = 0;
	while (i < size){
		read(fd, buff, 3);
		texture.colours[i].b = buff[0];
		texture.colours[i].g = buff[1];
		texture.colours[i].r = buff[2];
		i++;
	}
	// for (i = 0; i < size; i++){
	// 	printf("%x ", texture.colours[i].r);
	// 	printf("%x ", texture.colours[i].g);
	// 	printf("%x ", texture.colours[i].b);
	// 	printf("\n");
	// }
	return (texture);
}
