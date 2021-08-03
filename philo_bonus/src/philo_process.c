#include "philo_bonus.h"

static void	*monitor(void *ph_ch)
{
	t_philoch	*ph;

	ph = (t_philoch *)ph_ch;
	while (ph->start_t == 0)
		usleep(333);
	while (true)
	{
		if (get_time_ms() > ph->die_t)
		{
			usleep(333);
			exit(write_func("died\n", ph, DEATH_FLAG));
		}
	}
}

void	philo_process(t_philoch *ph)
{
	pthread_t	index;

	pthread_create(&index, NULL, monitor, ph);
	pthread_detach(index);
	philo(ph);
}
