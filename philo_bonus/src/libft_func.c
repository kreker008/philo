#include "philo_bonus.h"

static	int	ft_modul(int c)
{
	if (c < 0)
		return (-c);
	else
		return (c);
}

static	size_t	ft_writechar(char *int_ch, int n)
{
	int		n_mod;
	size_t	i;

	n_mod = 0;
	i = 0;
	if (n == 0)
	{
		i = 1;
		int_ch[0] = '0';
	}
	else
	{
		while (n)
		{
			n_mod = n % 10;
			int_ch[i++] = (char)(ft_modul(n_mod) + '0');
			n /= 10;
		}
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	int_ch[12];
	int		flag;
	size_t	size;
	size_t	j;
	char	*p;

	flag = 0;
	j = 0;
	if (n < 0)
		flag = 1;
	size = ft_writechar(int_ch, n);
	p = malloc(size + 1 + flag);
	if (p == NULL)
		return (NULL);
	p[size + flag] = 0;
	while (size)
		p[j++ + flag] = int_ch[size-- - 1];
	if (flag)
		p[0] = '-';
	return (p);
}

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

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*(s++))
		++size;
	return (size);
}
