#include "philo.h"

RET_S	give_fokrs(t_philoch *ph)
{
	if (get_time_ms() > ph->die_t)
		return (DEATH_FLAG);
	pthread_mutex_lock(ph->f_fork);
	//printf("%lu\t\t%lu\t\thas taken first fork\n", get_time_ms() -
	// ph->start_t, ph->order);
	write_func(get_time_ms() - ph->start_t, ph->order,
			   "is give first forks\n", ph, 0);
	if (get_time_ms() > ph->die_t)
		return (DEATH_FLAG);
	pthread_mutex_lock(ph->s_fork);
	//printf("%lu\t\t%lu\t\thas taken second fork\n", get_time_ms() -
	//		ph->start_t, ph->order);
	write_func(get_time_ms() - ph->start_t, ph->order,
			   "is give second forks\n", ph, 0);
	if (get_time_ms() > ph->die_t)
		return (DEATH_FLAG);
//	printf("%lu\t\t%lu\t\thas taken forks\n", get_time_ms() - ph->start_t,
//		   ph->order);
//	write_func(get_time_ms() - ph->start_t, ph->order, "is give forks\n", ph,
//			   0);
	return (0);
}

RET_S	try_eat(t_philoch *ph)
{
	if (give_fokrs(ph) == DEATH_FLAG)
		return (DEATH_FLAG);
//	printf("%lu\t\t%lu\t\tis eating\n", get_time_ms() - ph->start_t, ph->order);
	write_func(get_time_ms() - ph->start_t, ph->order, "is eating\n", ph, 0);
	if (get_time_ms() + ph->av->tte > ph->die_t)
	{
		wait_custom((ph->die_t + 1) - get_time_ms());
		return (DEATH_FLAG);
	}
	wait_custom(ph->av->tte);
	ph->die_t = get_time_ms() + ph->av->ttd;
	if (ph->av->ne != -1)
		++ph->eat_count;
	pthread_mutex_unlock(ph->f_fork);
	pthread_mutex_unlock(ph->s_fork);
	write_func(get_time_ms() - ph->start_t, ph->order,
			   "is drop forks\n", ph, 0);
	return (0);
}

RET_S	try_sleep(t_philoch *ph)
{
	size_t	actual_time;

	actual_time = get_time_ms();
	if (actual_time + ph->av->tts > ph->die_t)
	{
		wait_custom((ph->die_t + 1) - actual_time);
		return (DEATH_FLAG);
	}
//	printf("%lu\t\t%lu\t\tis sleeping\n", actual_time - ph->start_t, ph->order);
	write_func(get_time_ms() - ph->start_t, ph->order, "is sleeping\n", ph, 0);
	wait_custom(ph->av->tts);
	return (0);
}

RET_S	try_think(t_philoch *ph)
{
	if (ph->die_t < get_time_ms())
		return (DEATH_FLAG);
//	printf("%lu\t\t%lu\t\tis thinking\n", get_time_ms() - ph->start_t, ph->order);
	write_func(get_time_ms() - ph->start_t, ph->order, "is thinking\n", ph, 0);
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
		if (try_eat(ph) == DEATH_FLAG)
		{
			write_func(get_time_ms() - ph->start_t, ph->order,
					   "died\n", ph, DEATH_FLAG);
			ph->isdead = true;
			return (NULL);
		}
		if (try_sleep(ph) == DEATH_FLAG)
		{
			write_func(get_time_ms() - ph->start_t, ph->order,
					   "died\n", ph, DEATH_FLAG);
			ph->isdead = true;
			return (NULL);
		}

		if (try_think(ph) == DEATH_FLAG)
		{
			write_func(get_time_ms() - ph->start_t, ph->order,
					   "died\n", ph, DEATH_FLAG);
			ph->isdead = true;
			return (NULL);
		}
	}
}
