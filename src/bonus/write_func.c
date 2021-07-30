#include "philo_bonus.h"
#include "stdlib.h"

RET_S	c
{
	char *order_str;
	char *time_str;

	time_str = ft_itoa((int)time);
	order_str = ft_itoa((int)order);
	if (time_str == NULL)
		return EXIT_FAILURE; //exit_messege
	sem_wait(ph->print_sem);
	write(STDOUT_FILENO, time_str, ft_strlen(time_str));
	write(STDOUT_FILENO, "\t\t", 1);
	write(STDOUT_FILENO, order_str, ft_strlen(order_str));
	write(STDOUT_FILENO, "\t\t", 1);
	if (string != NULL)
		write(STDOUT_FILENO, string, ft_strlen(string));
	sem_post(ph->print_sem);
	free(time_str);
	free(order_str);
	return (ret);
}