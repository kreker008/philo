#include "philo_bonus.h"

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

static void	wait_simulation(t_philoch *ph, int *pid)
{
	int	i;
	int	ret_status;

	waitpid(WAIT_ANY, &ret_status, 0);
	i = -1;
	while (++i < ph[0].av->num)
		kill(pid[i], SIGKILL);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/start");
	sem_close(ph[0].sem);
	sem_close(ph[0].print_sem);
	sem_close(ph[0].start_sem);
}

static int	start_simulation(t_philoch *ph)
{
	int		i;
	pid_t	*pid;
	size_t	ph_num;

	ph_num = ph->av->num;
	i = -1;
	pid = malloc(sizeof(pid_t) * ph->av->num);
	if (pid == NULL)
		return (exit_message(EXIT_FAILURE, "allocate error\n"));
	while (++i < ph_num)
		sem_wait(ph[i].start_sem);
	i = -1;
	while (++i < ph_num)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			philo(&ph[i]);
	}
	wait_custom(500);
	i = -1;
	while (++i < ph_num)
		sem_post(ph[i].start_sem);
	wait_simulation(ph, pid);
	free(pid);
	return (0);
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

	if (ac == 5 || ac == 6)
	{
		if (isvalid_av(ac, av) == EXIT_FAILURE)
			return (exit_message(0, "invalid argv"));
		ret_status = init_philo(ac, av, &ph);
		if (ret_status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		start_simulation(ph);
		return (0);
	}
	else
		printf("Please, use 5 or 6 arguments\n");
	return (0);
}
