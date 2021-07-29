#include "philo_bonus.h"

RET_S	init_philo_forks(t_philoch **p_ch)
{
	int			i;
	sem_t 		*sem;
	t_philoch	*ph;

	ph = *p_ch;
	i = -1;
	sem_unlink("/semaphore");
	sem = sem_open("/semaphore", O_CREAT, 0666, ph[0].av->num);
	if (sem == SEM_FAILED)
		return EXIT_FAILURE; //exit_messege
	while (++i < ph[0].av->num)
		ph[i].sem = sem;
}