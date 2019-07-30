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

long			time_between_frames(void)
{
	static long ph_ms;
	long dms;

	// srand(time(0)); /* NEED THIS TO START THE TIME */
	if (ph_ms == 0)
		ph_ms = ft_milsec();
	dms = ft_milsec() - ph_ms;
	ph_ms = ft_milsec();
	return (dms);
}

static int seconds(void)
{
    time_t now;
    struct tm *tm;

    now = time(0);
    tm = localtime(&now);
    return (tm->tm_sec);
}

int     frames(void)
{
    static int frames;
    static int prev_sec;
	static int fps;
    int cur_sec;

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