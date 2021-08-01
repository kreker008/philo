#include "philo_bonus.h"

static RET_S	give_forks(t_philoch *ph)
{
	if (get_time_ms() > ph->die_t)
		return (DEATH_FLAG);
	sem_wait(ph->sem);
	if (get_time_ms() > ph->die_t)
		return (DEATH_FLAG);
	if (ph->av->num != 1)
		sem_wait(ph->sem);
	else
		wait_custom(ph->av->ttd + 1);
	if (get_time_ms() > ph->die_t)
		return (DEATH_FLAG);
	if (write_func("is give forks\n", ph, 0) == EXIT_FAILURE)
		return (DEATH_FLAG);
	return (0);
}

static RET_S	try_eat(t_philoch *ph)
{
	if (give_forks(ph) == DEATH_FLAG)
		return (DEATH_FLAG);
	if (write_func("is eating\n", ph, 0) == EXIT_FAILURE)
		return (DEATH_FLAG);
	if (get_time_ms() + ph->av->tte > ph->die_t)
	{
		wait_custom((ph->die_t + 1) - get_time_ms());
		return (DEATH_FLAG);
	}
	wait_custom(ph->av->tte);
	ph->die_t = get_time_ms() + ph->av->ttd;
	if (ph->av->ne != -1)
		++ph->eat_count;
	sem_post(ph->sem);
	sem_post(ph->sem);
	return (0);
}

static RET_S	try_sleep(t_philoch *ph)
{
	size_t	actual_time;

	actual_time = get_time_ms();
	if (actual_time + ph->av->tts > ph->die_t)
	{
		wait_custom((ph->die_t + 1) - actual_time);
		return (DEATH_FLAG);
	}
	if (write_func("is sleeping\n", ph, 0) == EXIT_FAILURE)
		return (DEATH_FLAG);
	wait_custom(ph->av->tts);
	return (0);
}

static RET_S	try_think(t_philoch *ph)
{
	if (ph->die_t < get_time_ms())
		return (DEATH_FLAG);
	if (write_func("is thinking\n", ph, 0) == EXIT_FAILURE)
		return (DEATH_FLAG);
	return (0);
}

int	philo(void *philo)
{
	t_philoch	*ph;

	ph = (t_philoch *)philo;
	sem_wait(ph->start_sem);
	ph->start_t = get_time_ms();
	ph->die_t = get_time_ms() + ph->av->ttd;
	while (true)
	{
		if (try_eat(ph) == DEATH_FLAG)
			return (write_func("died\n", ph, DEATH_FLAG));
		if (try_sleep(ph) == DEATH_FLAG)
			return (write_func("died\n", ph, DEATH_FLAG));
		if (try_think(ph) == DEATH_FLAG)
			return (write_func("died\n", ph, DEATH_FLAG));
	}
}
