#include "wolf3d.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		ft_putendl("Usage: ./wolf3d [map]");
	else
		init_wolf(argv[1]);
    return (0);
}
