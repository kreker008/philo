#include "philo_bonus.h"

void	wait_custom(size_t ms)
{
	size_t	end;

	end = get_time_ms() + ms;
	while (get_time_ms() < end)
		usleep(500);
}

size_t	get_time_ms(void)
{
	struct timeval	s_tval;

	gettimeofday(&s_tval, NULL);
	return (s_tval.tv_usec / 1000 + s_tval.tv_sec * 1000);
}
