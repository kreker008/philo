#include "philo_bonus.h"

RET_S	init_philo_sem(t_philoch **p_ch)
{
	int			i;
	sem_t 		*sem_forks;
	sem_t 		*sem_print;
	t_philoch	*ph;

	ph = *p_ch;
	i = -1;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_forks = sem_open("/forks", O_CREAT, 0666, ph[0].av->num);
	sem_print = sem_open("/print", O_CREAT, 0666, 1);
	if (sem_forks == SEM_FAILED)
		return EXIT_FAILURE; //exit_messege
	while (++i < ph[0].av->num)
	{
		ph[i].sem = sem_forks;
		ph[i].print_sem = sem_print;
	}
	return (0);
}