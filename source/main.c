/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:50:37 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/23 11:50:49 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_putendl("Usage: ./wolf3d [map]");
	else
		init_wolf(argv[1]);
	return (0);
}
