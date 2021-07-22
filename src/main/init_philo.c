#include "Philo.h"

void	init_philo_forks(t_philoch **p_ch)
{
	int	i;
	t_philoch *ph_ch;

	ph_ch = *p_ch;
	i = 0;
	while(i < ph_ch[0].av->num)
		pthread_mutex_init(&ph_ch[0].forks[i++], NULL);
	i = -1;
	while(++i + 1 < ph_ch[0].av->num)
		if(i % 2 == 0)
		{
			ph_ch[i].f_fork = &ph_ch[0].forks[i];
			ph_ch[i].s_fork = &ph_ch[0].forks[i + 1];
		}
		else
		{
			ph_ch[i].s_fork = &ph_ch[0].forks[i];
			ph_ch[i].f_fork = &ph_ch[0].forks[i + 1];
		}
	if(i % 2 == 0)
	{
		ph_ch[i].f_fork = &ph_ch[0].forks[i];
		ph_ch[i].s_fork = &ph_ch[0].forks[0];
	}
	else
	{
		ph_ch[i].s_fork = &ph_ch[0].forks[i];
		ph_ch[i].f_fork = &ph_ch[0].forks[0];
	}
}

static void	init_philo_av(int ac, const char **av, t_philoav *p_av)
{
	*p_av = (t_philoav) {0};
	p_av->num = ft_atoi(av[1]);
	p_av->ttd = ft_atoi(av[2]);
	p_av->tte = ft_atoi(av[3]);
	p_av->tts = ft_atoi(av[4]);
	if (ac == 5)
		p_av->ne = -1;
	else
		p_av->ne = p_av->num = ft_atoi(av[5]);
}

static void	init_philo_order(t_philoch **p_ch)
{
	int i;
	t_philoch *ph_ch;

	ph_ch = *p_ch;
	i = -1;
	while(++i < ph_ch[0].av->num)
		ph_ch[i].order = i;
}

static void init_philo_av_to_ch(t_philoch **p_ch, t_philoav *p_av)
{
	int i;
	t_philoch *ph_ch;

	ph_ch = *p_ch;
	i = -1;
	while(++i < p_av->num)
		ph_ch[i].av = p_av;
}

/*
 * argv[1] - number_of_philosophers,
 * argv[2] - time_to_die
 * argv[3] - time_to_eat
 * argv[4] - time_to_sleep
 * argv[5] - num...
 */
ret_s	init_philo(int ac, const char **argv, t_philoch	**ph)
{
	t_philoav	*av;

	av = malloc(sizeof(t_philoav));
	if (av == NULL)
		return -1;//(exit_massege())
	init_philo_av(ac, argv, av);
	*ph = malloc(sizeof(t_philoch) * av->num);
	if (*ph == NULL)
		return -1;//(exit_massege())
	init_philo_av_to_ch(ph, av);
	(*ph[0]).forks = malloc(sizeof(pthread_mutex_t) * av->num);
	if ((*ph)->forks == NULL)
		return -1;//(exit_massege())
	init_philo_forks(ph);
	init_philo_order(ph);
	return (0);
}