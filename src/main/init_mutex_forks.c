#include "Philo.h"

static void	set_forks_to_philo(t_philoch **p_ch, int i)
{
	t_philoch	*ph;

	ph = *p_ch;
	if (i % 2 == 0)
	{
		ph[i].f_fork = &ph[0].forks[i];
		ph[i].s_fork = &ph[0].forks[i + 1];
	}
	else
	{
		ph[i].s_fork = &ph[0].forks[i];
		ph[i].f_fork = &ph[0].forks[i + 1];
	}
}

void	init_philo_forks(t_philoch **p_ch)
{
	int			i;
	t_philoch	*ph;

	ph = *p_ch;
	i = 0;
	while (i < ph[0].av->num)
		pthread_mutex_init(&ph[0].forks[i++], NULL);
	i = -1;
	while (++i + 1 < ph[0].av->num)
		set_forks_to_philo(p_ch, i);
	if (i % 2 == 0)
	{
		ph[i].f_fork = &ph[0].forks[i];
		ph[i].s_fork = &ph[0].forks[0];
	}
	else
	{
		ph[i].s_fork = &ph[0].forks[i];
		ph[i].f_fork = &ph[0].forks[0];
	}
}
