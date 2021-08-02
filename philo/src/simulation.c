#include "philo.h"

RET_S	try_eat(t_philoch *ph)
{
	pthread_mutex_lock(ph->l_fork);
	if (write_func("has taken first fork\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_lock(ph->r_fork);
	if (write_func("has taken second fork\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ph->die_t = get_time_ms() + ph->av->ttd;
	if (write_func("is eating\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_custom(ph->av->tte);
	if (ph->av->ne != -1)
		++ph->eat_count;
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
	return (0);
}

RET_S	try_sleep(t_philoch *ph)
{
	if (write_func("is sleeping\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_custom(ph->av->tts);
	return (0);
}

RET_S	try_think(t_philoch *ph)
{
	if (write_func("is thinking\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}

void	*philo(void *philo)
{
	t_philoch	*ph;

	ph = (t_philoch *)philo;
	pthread_mutex_lock(&ph->start_mut[ph->order - 1]);
	ph->start_t = get_time_ms();
	ph->die_t = get_time_ms() + ph->av->ttd;
	if (ph->order % 2 == 0)
		wait_custom(10);
	while (true)
	{
		if (try_eat(ph) == EXIT_FAILURE)
			ph->die_t = 0;
		if (try_sleep(ph) == EXIT_FAILURE)
			ph->die_t = 0;
		if (try_think(ph) == EXIT_FAILURE)
			ph->die_t = 0;
	}
}
