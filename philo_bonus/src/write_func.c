#include "philo_bonus.h"

RET_S	write_func(char *string, t_philoch *ph,	int ret)
{
	size_t	time;
	char	*order_str;
	char	*time_str;

	time = get_time_ms() - ph->start_t;
	time_str = ft_itoa((int)time);
	order_str = ft_itoa((int)ph->order);
	if (time_str == NULL || order_str == NULL)
		return (exit_message(EXIT_FAILURE, "malloc error"));
	sem_wait(ph->print_sem);
	write(STDOUT_FILENO, time_str, ft_strlen(time_str));
	write(STDOUT_FILENO, "\t\t", 2);
	write(STDOUT_FILENO, order_str, ft_strlen(order_str));
	write(STDOUT_FILENO, "\t\t", 2);
	if (string != NULL)
		write(STDOUT_FILENO, string, ft_strlen(string));
	free(time_str);
	free(order_str);
	if (ret == 0 || ret == FULL)
		sem_post(ph->print_sem);
	return (ret);
}

RET_S	exit_message(int err_status, char *message)
{
	write(1, message, ft_strlen(message));
	return (err_status);
}
