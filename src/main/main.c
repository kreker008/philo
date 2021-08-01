#include "philo.h"

static void	check_stop(t_philoch *ph)
{
	int		i;
	bool	*ne_flag;

	ne_flag = (bool[2]){false};
	if (ph->av->ne != -1)
		ne_flag[0] = true;
	while (true)
	{
		i = -1;
		while (++i < ph->av->num)
		{
			if (ne_flag[0] && ph[i].eat_count < ph[i].av->ne)
				ne_flag[1] = false;
			if (ph[i].isdead)
				return ;
		}
		if (ne_flag[0] && ne_flag[1])
		{
			pthread_mutex_lock(ph[0].print_mut);
			return ;
		}

		else if (ne_flag[0])
			ne_flag[1] = true;
	}
}

static void	start_simulation(t_philoch *ph)
{
	int	i;

	i = -1;
	while (++i < ph[0].av->num)
		pthread_mutex_lock(&ph[i].start_mut[i]);
	i = -1;
	while (++i < ph[0].av->num)
		pthread_create(&ph[i].index, NULL, philo, &ph[i]);
	i = -1;
	while (++i < ph->av->num)
		pthread_detach(ph[i].index);
	wait_custom(500);
	i = -1;
	while (++i < ph[0].av->num)
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
	int			ret_status;
	t_philoch	*ph;

	//if(isvalid_av(av))
	//	return (exit_messege());
	if (ac == 5 || ac == 6)
	{
		ret_status = init_philo(ac, av, &ph);
		if (ret_status == -1)
			return (-1);
		start_simulation(ph);
		return (0);
	}
	else
		printf("Please, use 5 or 6 arguments\n");
	return (0);
}
