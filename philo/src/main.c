#include "philo.h"

static RET_S	isvalid_av(int ac, const char **av)
{
	int	num;

	num = ft_atoi(av[1]);
	if (num < 1)
		return (EXIT_FAILURE);
	num = ft_atoi(av[2]);
	if (num < 1)
		return (EXIT_FAILURE);
	num = ft_atoi(av[3]);
	if (num < 1)
		return (EXIT_FAILURE);
	num = ft_atoi(av[4]);
	if (num < 1)
		return (EXIT_FAILURE);
	if (ac == 5)
		return (0);
	num = ft_atoi(av[5]);
	if (num < 1)
		return (EXIT_FAILURE);
	return (0);
}

static RET_S	check_stop(t_philoch *ph)
{
	int		i;
	bool	*ne_flag;

	ne_flag = (bool[2]){false};
	if (ph->av->ne != -1)
		ne_flag[0] = true;
	usleep(333);
	while (true)
	{
		i = -1;
		while (++i < (int)ph->av->num)
		{
			if (ne_flag[0] && (int)ph[i].eat_count < ph[i].av->ne)
				ne_flag[1] = false;
			if (get_time_ms() > ph[i].die_t)
				return (write_func("died\n", &ph[i], DEATH_FLAG));
		}
		if (ne_flag[0] && ne_flag[1])
		{
			pthread_mutex_lock(ph[0].print_mut);
			return (0);
		}
		else if (ne_flag[0])
			ne_flag[1] = true;
	}
}

static void	start_simulation(t_philoch *ph)
{
	int	i;

	i = -1;
	while (++i < (int)ph[0].av->num)
		pthread_mutex_lock(&ph[i].start_mut[i]);
	i = -1;
	while (++i < (int)ph[0].av->num)
		pthread_create(&ph[i].index, NULL, philo, &ph[i]);
	i = -1;
	while (++i < (int)ph->av->num)
		pthread_detach(ph[i].index);
	wait_custom(500);
	i = -1;
	while (++i < (int)ph[0].av->num)
		pthread_mutex_unlock(&ph[i].start_mut[i]);
	check_stop(ph);
}

/*
 * av[1] - number_of_philosophers,
 * av[2] - time_to_die
 * av[3] - time_to_eat
 * av[4] - time_to_sleep
 * av[5] - eating num
 */
int	main(int ac, const char **av)
{
	t_philoch	*ph;

	if (ac == 5 || ac == 6)
	{
		if (isvalid_av(ac, av) == EXIT_FAILURE)
			return (exit_message(0, "invalid argv\n"));
		if (init_philo(ac, av, &ph) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		start_simulation(ph);
		return (0);
	}
	else
		printf("Please, use 5 or 6 arguments\n");
	return (0);
}
