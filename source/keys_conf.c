/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys_conf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:51:27 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/24 11:26:12 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdlib.h>

int	close_window(void *ptr)
{
	(void)ptr;
	exit(0);
	return (0);
}

int	key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		close_window(NULL);
	else if (key == KEY_S)
		CONTROLS->back = 1;
	else if (key == KEY_W)
		CONTROLS->front = 1;
	else if (key == KEY_D)
		CONTROLS->right = 1;
	else if (key == KEY_A)
		CONTROLS->left = 1;
	else if (key == KEY_RIGHT)
		CONTROLS->look_right = 1;
	else if (key == KEY_LEFT)
		CONTROLS->look_left = 1;
	else if (key == KEY_LSHIFT)
		CONTROLS->run = 1;
	else if (key == KEY_SPACE)
		CONTROLS->shoot = 1;
	return (0);
}

int	key_release(int key, t_mlx *mlx)
{
	if (key == KEY_LSHIFT)
		CONTROLS->run = 0;
	else if (key == KEY_W)
		CONTROLS->front = 0;
	else if (key == KEY_S)
		CONTROLS->back = 0;
	else if (key == KEY_A)
		CONTROLS->left = 0;
	else if (key == KEY_D)
		CONTROLS->right = 0;
	else if (key == KEY_LEFT)
		CONTROLS->look_left = 0;
	else if (key == KEY_RIGHT)
		CONTROLS->look_right = 0;
	else if (key == KEY_SPACE)
		CONTROLS->shoot = 0;
	return (0);
}
