#include "Philo.h"

void	print_eat_num(t_philoch *ph)
{
	size_t	i;

	i = 0;
	while (i < ph[0].av->num)
	{
		printf("%lu is eating %lu\n", ph[i].order, ph[i].eat_count);
		++i;
	}
}

void	check_stop(t_philoch *ph)
{
	int		i;
	bool	ne_flag;
	bool	stop_flag;

	i = 0;
	ne_flag = false;
	stop_flag = false;
	if (ph->av->ne != -1)
		ne_flag = true;
	while(true)
	{
		while(i < ph->av->num)
		{
			if (ne_flag && ph[i].eat_count < ph[i].av->ne)
				stop_flag = false;
			if (ph[i].isdead)
			{
				printf("%lu %lu is dead\n", get_time_ms(), ph[i].order);
				return;
			}
			++i;
		}
		if (ne_flag && stop_flag)
			return;
		else if (ne_flag)
			stop_flag = true;
		i = 0;
	}

}

void	start_simulation(t_philoch *ph)
{
	int i;

	i = -1;
	while(++i < ph[0].av->num)
		pthread_create(&ph[i].index, NULL, philo, &ph[i]);
	i = -1;
	while(++i < ph->av->num)
		pthread_detach(ph[i].index);
	check_stop(ph);
}
/*
 * av[1] - number_of_philosophers,
 * av[2] - time_to_die
 * av[3] - time_to_eat
 * av[4] - time_to_sleep
 * av[5] - eating num
 */
int main(int ac, const char **av)
{
	int			ret_status;
	t_philoch	*ph;

	//if(isvalid_av(av))
	//	return (exit_messege());
	ret_status = -1;
	if(ac == 5 || ac == 6)
	{
		ret_status = init_philo(ac, av, &ph);
		if (ret_status == -1)
			return (-1);
		start_simulation(ph);
		return(0);
	}
	else
		printf("Please, use 5 or 6 arguments\n");
	return 0;
}
