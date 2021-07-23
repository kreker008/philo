#include "Philo.h"

void	set_forks_to_philo(t_philoch **p_ch, int i)
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