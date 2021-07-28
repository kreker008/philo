#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int						flag;
	unsigned long long int	source;

	flag = 1;
	source = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			flag = -1;
		++str;
	}
	if (!(*str <= '9' && *str >= '0'))
		return (0);
	while (*str <= '9' && *str >= '0')
	{
		source = (source * 10) + (*str++ - '0');
		if (source > 9223372036854775807 && flag == 1)
			return (-1);
		else if (source > 9223372036854775807 && flag == -1)
			return (0);
	}
	return (source * flag);
}
