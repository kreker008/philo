#include "philo.h"

RET_S	give_fokrs(t_philoch *ph)
{
	if (get_time_ms() > ph->die_t)
	{
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	//printf("%lu\t\t%lu\t\thas taken first fork\n", get_time_ms() -
	// ph->start_t,
	//		ph->order);
	pthread_mutex_lock(ph->f_fork);
	if (get_time_ms() > ph->die_t)
	{
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	//printf("%lu\t\t%lu\t\thas taken second fork\n", get_time_ms() -
	//		ph->start_t, ph->order);
	pthread_mutex_lock(ph->s_fork);
	if (get_time_ms() > ph->die_t)
	{
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	printf("%lu\t\t%lu\t\thas taken forks\n", get_time_ms() - ph->start_t,
		   ph->order);
	return (0);
}

RET_S	try_eat(t_philoch *ph)
{
	if (give_fokrs(ph) == DEATH_FLAG)
		return (DEATH_FLAG);
	printf("%lu\t\t%lu\t\tis eating\n", get_time_ms() - ph->start_t, ph->order);
	if (get_time_ms() + ph->av->tte > ph->die_t)
	{
		wait_custom((ph->die_t + 1) - get_time_ms());
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	wait_custom(ph->av->tte);
	ph->die_t = get_time_ms() + ph->av->ttd;
	if (ph->av->ne != -1)
		++ph->eat_count;
	pthread_mutex_unlock(ph->f_fork);
	pthread_mutex_unlock(ph->s_fork);
	return (0);
}

RET_S	try_sleep(t_philoch *ph)
{
	size_t	actual_time;

	actual_time = get_time_ms();
	if (actual_time + ph->av->tts > ph->die_t)
	{
		wait_custom((ph->die_t + 1) - actual_time);
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	printf("%lu\t\t%lu\t\tis sleeping\n", actual_time - ph->start_t, ph->order);
	wait_custom(ph->av->tts);
	return (0);
}

RET_S	try_think(t_philoch *ph)
{
	if (ph->die_t < get_time_ms())
	{
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	printf("%lu\t\t%lu\t\tis thinking\n", get_time_ms() - ph->start_t, ph->order);
	return (0);
}

void	*philo(void *philo)
{
	t_philoch	*ph;

	ph = (t_philoch *)philo;
	ph->start_t = get_time_ms();
	ph->die_t = get_time_ms() + ph->av->ttd;
	if (ph->order % 2 == 1)
		wait_custom(10);
	while (true)
	{
		if (try_eat(ph) == DEATH_FLAG)
			return (NULL);
		if (try_sleep(ph) == DEATH_FLAG)
			return (NULL);
		if (try_think(ph) == DEATH_FLAG)
			return (NULL);
	}
}
