#include "philo.h"

static void	set_forks_to_philo(t_philoch **p_ch, int i,
								  pthread_mutex_t	*all_forks)
{
	t_philoch	*ph;

	ph = *p_ch;
	if (i % 2 == 0)
	{
		ph[i].f_fork = &all_forks[i];
		ph[i].s_fork = &all_forks[i + 1];
	}
	else
	{
		ph[i].s_fork = &all_forks[i];
		ph[i].f_fork = &all_forks[i + 1];
	}
}

RET_S	init_philo_forks(t_philoch **p_ch)
{
	int				i;
	t_philoch		*ph;
	pthread_mutex_t	*all_forks;

	ph = *p_ch;
	all_forks = malloc(sizeof(pthread_mutex_t) * ph->av->num);
	if (all_forks == NULL)
		return (exit_message(EXIT_FAILURE, "allocate error"));
	i = -1;
	while (++i < ph[0].av->num)
		pthread_mutex_init(&all_forks[i], NULL);
	i = -1;
	while (++i + 1 < ph[0].av->num)
		set_forks_to_philo(p_ch, i, all_forks);
	if (i % 2 == 0)
	{
		ph[i].f_fork = &all_forks[i];
		ph[i].s_fork = &all_forks[0];
	}
	else
	{
		ph[i].s_fork = &all_forks[i];
		ph[i].f_fork = &all_forks[0];
	}
	return (0);
}

RET_S	init_start_mutex(t_philoch **p_ch)
{
	int				i;
	t_philoch		*ph;
	pthread_mutex_t	*all_mutex;

	ph = *p_ch;
	all_mutex = malloc(sizeof(pthread_mutex_t) * ph->av->num);
	if (all_mutex == NULL)
		return (exit_message(EXIT_FAILURE, "allocate error"));
	i = -1;
	while (++i < ph[0].av->num)
		pthread_mutex_init(&all_mutex[i], NULL);
	i = -1;
	while (++i < ph[0].av->num)
		ph[i].start_mut = all_mutex;
	return (0);
}

RET_S	init_print_mutex(t_philoch **p_ch)
{
	int				i;
	t_philoch		*ph;
	pthread_mutex_t	*print_mut;

	ph = *p_ch;
	print_mut = malloc(sizeof(pthread_mutex_t));
	if (print_mut == NULL)
		return (exit_message(EXIT_FAILURE, "allocate error"));
	pthread_mutex_init(print_mut, NULL);
	i = -1;
	while (++i < ph[0].av->num)
		ph[i].print_mut = print_mut;
	return (0);
}
