#include "philo_bonus.h"

RET_S	init_philo_sem(t_philoch **p_ch)
{
	int			i;
	sem_t 		*sem[3];
	t_philoch	*ph;

	ph = *p_ch;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/start");
	sem[0] = sem_open("/forks", O_CREAT, 0666, ph[0].av->num);
	if (sem[0] == SEM_FAILED)
		return EXIT_FAILURE; //exit_messege
	sem[1] = sem_open("/start", O_CREAT, 0666, ph[0].av->num);
	if (sem[1] == SEM_FAILED)
		return EXIT_FAILURE; //exit_messege
	sem[2] = sem_open("/print", O_CREAT, 0666, 1);
	if (sem[2] == SEM_FAILED)
		return EXIT_FAILURE; //exit_messege
	i = -1;
	while (++i < ph[0].av->num)
	{
		ph[i].sem = sem[0];
		ph[i].start_sem = sem[1];
		ph[i].print_sem = sem[2];
	}
	return (0);
}