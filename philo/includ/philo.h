#ifndef PHILO_H
# define PHILO_H

# include "stdbool.h"
# include "stdio.h"
# include "sys/time.h"
# include <unistd.h>
# include "stdlib.h"
# include <pthread.h>

# define RET_S		int
# define DEATH_FLAG	-2

/*
 * 	num - number_of_philosophers / forks
 *  ttd - time_to_die
 *  tte - time_to_eat
 *  tts - time_to_sleap
 */
typedef struct s_philoav
{
	size_t		num;
	size_t		ttd;
	size_t		tte;
	size_t		tts;
	int			ne;
}				t_philoav;

typedef struct s_philoch
{
	size_t					order;
	pthread_t				index;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*start_mut;
	pthread_mutex_t			*print_mut;
	size_t					die_t;
	size_t					start_t;
	size_t					eat_count;
	t_philoav				*av;
}							t_philoch;

/*
 *		init_philo.c
 */
RET_S	init_philo(int ac, const char **argv, t_philoch	**ph);

/*
 *		ft_atoi.c
 */
int		ft_atoi(const char *str);

/*
 * 		sumulation.c
 */
void	*philo(void *philo);

/*
 *		libft_func.c
 */
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);

/*
 * 		time.c
 */
size_t	get_time_ms(void);
void	wait_custom(size_t ms);

/*
 * 		init_mutex.c
 */
RET_S	init_philo_forks(t_philoch **p_ch);
RET_S	init_start_mutex(t_philoch **p_ch);
RET_S	init_print_mutex(t_philoch **p_ch);

/*
 * 		write_func.c
 */
RET_S	write_func(char *string, t_philoch *ph,	int ret);
RET_S	exit_message(int err_status, char *message);

#endif
