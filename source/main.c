#include "wolf3d.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
	printf("%.1f\n", sqrt(9));
	printf("%.1f\n", pow(3, 2));
	if (argc != 2)
		ft_putendl("Usage: ./wolf3d [map]");
	else
		init_wolf(argv[1]);
  return (0);
}
