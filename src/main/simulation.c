#include "Philo.h"

ret_s	give_fokrs(t_philoch *ph)
{
	if (ph->die_t <= get_time_ms())
	{
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	if (ph->order % 2 == 0)
		wait_custom(10);
	pthread_mutex_lock(ph->f_fork);
	if (ph->die_t <= get_time_ms())
	{
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	pthread_mutex_lock(ph->s_fork);
	if (ph->die_t == get_time_ms())
	{
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	return (0);
}

ret_s	try_eat(t_philoch *ph)
{
	if (give_fokrs(ph) == DEATH_FLAG)
	{
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	printf("%lu %lu is eating\n", get_time_ms() - ph->start_t, ph->order );
	wait_custom(ph->av->tte);
	if (ph->av->ne != -1)
		++ph->eat_count;
	pthread_mutex_unlock(ph->f_fork);
	pthread_mutex_unlock(ph->s_fork);
	ph->die_t = get_time_ms() + ph->av->ttd;
	return (0);
}

ret_s try_sleep(t_philoch *ph)
{
	size_t actual_time;

	actual_time = get_time_ms();
	if(ph->die_t <= actual_time + ph->av->tts)
	{
		wait_custom(ph->die_t - actual_time);
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	printf("%lu %lu is sleeping\n", actual_time - ph->start_t, ph->order);
	wait_custom(ph->av->tts);
	return (0);
}

ret_s try_think(t_philoch *ph)
{
	size_t actual_time;

	actual_time = get_time_ms();
	if(ph->die_t <= actual_time)
	{
		ph->isdead = true;
		return (DEATH_FLAG);
	}
	printf("%lu %lu is thinking\n", actual_time - ph->start_t, ph->order );
	return (0);
}

void	*philo(void *philo)
{
	t_philoch *ph;

	ph = (t_philoch *)philo;
	ph->start_t = get_time_ms();
	ph->die_t = get_time_ms() + ph->av->ttd;
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