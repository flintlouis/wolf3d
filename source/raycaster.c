#include "wolf3d.h"

double	to_radians(int degrees)
{
	return (degrees * (PI / 180));
}

int map[7][7] = 
{
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1},
}

void	raycaster(void)
{
	double viewing_angle;
	int x_intersect;
	int y_intersect;
	int player_y;
	int player_x;
	int dy;
	int dx;
	// int plane; // aantal rays (voor iedere x colom 1 ray)
	
	// plane = 300;
	viewing_angle = to_radians(45);
	printf("%lf\n", viewing_angle);
	player_x = 30;
	player_y = 70;
	dy = player_y;
	y_intersect = player_y - dy;
	x_intersect = player_x - dy / tan(viewing_angle);
	printf("First intersect -> x: %d, y: %d", x_intersect, y_intersect);
}
