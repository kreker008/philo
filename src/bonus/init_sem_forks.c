#include "philo_bonus.h"

void	init_philo_forks(t_philoch **p_ch)
{
	int			i;
	sem_t 		*sem;
	t_philoch	*ph;

	ph = *p_ch;
	i = -1;
	sem = sem_open("MY_SEMAPHORE", O_CREAT, 0666, ph[0].av->num / 2);
	while (++i < ph[0].av->num)
		ph[i].sem = sem;
}