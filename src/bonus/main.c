#include "philo_bonus.h"

static int	start_simulation(t_philoch *ph)
{
	int		i;
	pid_t	pid[ph->av->num];
	int		ret_status;
	size_t	ph_num;

	i = -1;
	ph_num = ph->av->num;
	while(++i < ph_num)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			ret_status = philo(&ph[i]);
			break;
		}
	}
	if (pid[i] != 0)
	{
		i = -1;
		waitpid(WAIT_ANY, &ret_status, 0);
		while(++i < ph_num)
			kill(pid[i], 0); //FIX KILLSIG
		printf("return status %i\n", (signed char)WEXITSTATUS(ret_status));
		sem_unlink("/forks");
		sem_unlink("/print");
		sem_close(ph[0].sem);
		sem_close(ph[0].print_sem);
		if (WTERMSIG(ret_status) == DEATH_FLAG)
		{

			printf("DEATH\n");
			return (0);
		}
	}
	return (ret_status);
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
		if (ret_status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (start_simulation(ph));
	}
	else
		write(1, "Please, use 5 or 6 arguments\n", 30);
	return (0);
}