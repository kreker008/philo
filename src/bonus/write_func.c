#include "philo_bonus.h"
#include "stdlib.h"

RET_S	write_func(size_t time, size_t order, char *string)
{
	char *order_str;
	char *time_str;

	time_str = ft_itoa((int)time);
	if (time_str == NULL)
		return EXIT_FAILURE; //exit_messege
	write(STDOUT_FILENO, time_str, ft_strlen(time_str));
	write(STDOUT_FILENO, "\t\t", 1);
	order_str = ft_itoa((int)order);
	if (order_str == NULL)
		return EXIT_FAILURE; //exit_messege
	write(STDOUT_FILENO, order_str, ft_strlen(order_str));
	write(STDOUT_FILENO, "\t\t", 1);
	if (string != NULL)
		write(STDOUT_FILENO, string, ft_strlen(string));
}