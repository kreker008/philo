#include "philo_bonus.h"

static int	start_simulation(t_philoch *ph)
{
	int		i;
	pid_t	pid;
	int		ret_status;

	i = -1;
	while(++i < ph->av->num)
	{
		pid = fork();
		if (pid == 0)
		{
			ret_status = philo(&ph[i]);
			break;
		}
	}
	if (pid != 0)
	{
		//waitpid(WAIT_ANY, &ret_status, 0);
		wait_custom(1000 * 2);
		kill(0, 9); //FIX KILLSIG
		sem_unlink("/forks");
		sem_unlink("/print");
		printf("return status %i\n", WEXITSTATUS(ret_status));
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