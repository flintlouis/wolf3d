/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_milsec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/10 17:25:46 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/10 17:28:25 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

long	ft_milsec(void)
{
	long				ns;
	time_t				s;
	struct timespec		spec;

	clock_gettime(CLOCK_REALTIME, &spec);
	s = spec.tv_sec;
	ns = spec.tv_nsec;
	return (s * 1000 + ns / 1000000);
}
