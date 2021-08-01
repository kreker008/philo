#include "philo.h"

RET_S	write_func(size_t time, size_t order, char *string, t_philoch *ph,
					int ret)
{
	char *order_str;
	char *time_str;

	time_str = ft_itoa((int)time);
	order_str = ft_itoa((int)order);
	pthread_mutex_lock(ph->print_mut);
	if (time_str == NULL)
		return EXIT_FAILURE; //exit_messege
	write(STDOUT_FILENO, time_str, ft_strlen(time_str));
	write(STDOUT_FILENO, "\t\t", 1);
	write(STDOUT_FILENO, order_str, ft_strlen(order_str));
	write(STDOUT_FILENO, "\t\t", 1);
	if (string != NULL)
		write(STDOUT_FILENO, string, ft_strlen(string));
	free(time_str);
	free(order_str);
	if(ret == 0)
		pthread_mutex_unlock(ph->print_mut);
	return (ret);
}