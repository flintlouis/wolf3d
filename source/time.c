/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:52:00 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/24 11:23:33 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

static long		ft_milsec(void)
{
	long				ns;
	time_t				s;
	struct timespec		spec;

	clock_gettime(CLOCK_REALTIME, &spec);
	s = spec.tv_sec;
	ns = spec.tv_nsec;
	return (s * 1000 + ns / 1000000);
}

/*
** Calculate the mil sec between each frame
*/

long			time_between_frames(void)
{
	static long	ph_ms;
	long		delta_ms;

	if (ph_ms == 0)
		ph_ms = ft_milsec();
	delta_ms = ft_milsec() - ph_ms;
	ph_ms = ft_milsec();
	return (delta_ms);
}

static	int		seconds(void)
{
	time_t		now;
	struct tm	*tm;

	now = time(0);
	tm = localtime(&now);
	return (tm->tm_sec);
}

/*
** Calculate how many frames per second
*/

int				frames(void)
{
	static int	frames;
	static int	prev_sec;
	static int	fps;
	int			cur_sec;

	frames++;
	cur_sec = seconds();
	if (cur_sec != prev_sec)
	{
		prev_sec = cur_sec;
		fps = frames;
		frames = 0;
		return (fps);
	}
	return (fps);
}
