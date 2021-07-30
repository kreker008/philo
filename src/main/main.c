#include "philo.h"

static void	start_simulation(t_philoch *ph)
{
	int	i;

	i = -1;
	while (++i < ph[0].av->num)
		pthread_create(&ph[i].index, NULL, philo, &ph[i]);
	i = -1;
	while (++i < ph->av->num)
		pthread_detach(ph[i].index);
	i = -1;
	while (true)
	{
		while (++i < ph->av->num)
		{
			if (ph[i].isdead)
			{
				printf("%lu\t\t%lu\t\tis dead\n", get_time_ms() - ph->start_t,
					   ph[i].order);
				return ;
			}
		}
		i = -1;
	}
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
