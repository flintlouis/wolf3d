#include "wolf3d.h"
#include <math.h>

double to_radians(double degrees)
{
    return (degrees * (M_PI / 180.0));
}

static t_dpoint get_unit_x(double rot)
{
	t_dpoint v;
	v.x = cos(rot);
	v.y = sin(rot);

	return v;
}

static t_dpoint get_unit_y(double rot)
{
	t_dpoint v;
	v.x = -sin(rot);
	v.y = cos(rot);

	return v;
}

static void multiply_vector(double m, t_dpoint *vector)
{
	vector->x *= m;
	vector->y *= m;
}

static t_dpoint add_vector(t_dpoint *a, t_dpoint *b)
{
	t_dpoint sum;

	sum.x = a->x + b->x;
	sum.y = a->y + b->y;

	return sum;
}

t_dpoint sub_vector(t_dpoint *a, t_dpoint *b)
{
	t_dpoint sub;

	sub.x = a->x - b->x;
	sub.y = a->y - b->y;

	return sub;
}

void	rotate_vector(t_dpoint *vector, double rad)
{
	double tmpx;

	t_dpoint ux = get_unit_x(rad);
	t_dpoint uy = get_unit_y(rad);

	multiply_vector(vector->x, &ux);
	multiply_vector(vector->y, &uy);

	t_dpoint sum = add_vector(&ux, &uy);

	vector->x = sum.x;
	vector->y = sum.y;

	// tmpx = vector->x;
	// vector->x = tmpx * cos(rad) - vector->y * sin(rad);
	// vector->y = tmpx * sin(rad) + vector->y * cos(rad);
}

static void set_vector(t_dpoint *vector, double angle, double distance)
{
	vector->x = 0;
	vector->y = 1;

	rotate_vector(vector, to_radians(angle));
	multiply_vector(distance, vector);
}

void	set_player_angle(t_player *player, double degrees)
{
	player->angle = degrees;

	if (player->angle < 0)
		player->angle += 360;
	else if (player->angle > 360)
		player->angle -= 360;

	set_vector(&player->looking_dir,player->angle, 1);
	set_vector(&player->plane,player->angle + 90, 0.66);
	
}

void	player_look(t_mlx *mlx)
{
	if (CONTROLS->look_right)
		set_player_angle(PLAYER, PLAYER->angle + 1.5);
	if (CONTROLS->look_left)
		set_player_angle(PLAYER, PLAYER->angle - 1.5);
}