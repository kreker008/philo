#include "philo_bonus.h"

static RET_S	try_eat(t_philoch *ph)
{
	sem_wait(ph->sem);
	if (write_func("has taken first fork\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	sem_wait(ph->sem);
	if (write_func("has taken second fork\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (write_func("is eating\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ph->die_t = get_time_ms() + ph->av->ttd;
	wait_custom(ph->av->tte);
	if (ph->av->ne != -1)
		if ((int)++ph->eat_count >= ph->av->ne)
			exit(FULL);
	sem_post(ph->sem);
	sem_post(ph->sem);
	return (0);
}

static RET_S	try_sleep(t_philoch *ph)
{
	if (write_func("is sleeping\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_custom(ph->av->tts);
	return (0);
}

static RET_S	try_think(t_philoch *ph)
{
	if (write_func("is thinking\n", ph, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}

int	philo(void *philo)
{
	t_philoch	*ph;

	ph = (t_philoch *)philo;
	sem_wait(ph->start_sem);
	ph->start_t = get_time_ms();
	ph->die_t = get_time_ms() + ph->av->ttd;
	if (ph->order % 2 == 0)
		wait_custom(10);
	while (true)
	{
		if (try_eat(ph) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (try_sleep(ph) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (try_think(ph) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
	}
}
