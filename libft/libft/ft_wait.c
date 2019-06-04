/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wait.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/10 17:26:15 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/10 17:31:18 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

void	ft_wait(int sec, long nano)
{
	struct timespec tim;
	struct timespec tim2;

	tim.tv_sec = sec;
	tim.tv_nsec = nano;
	nanosleep(&tim, &tim2);
}
