#ifndef PHILO_H
# define PHILO_H

#include "stdbool.h"
#include "stdio.h"
#include "sys/time.h"
#include <unistd.h>
#include "stdlib.h"
#include "errno.h"
#include <pthread.h>

#define ret_s		int
#define DEATH_FLAG	-2

/*
 * 	num - number_of_philosophers / forks
 *  ttd - time_to_die
 *  tte - time_to_eat
 *  tts - time_to_sleap
 */
typedef struct	s_philoav
{
	size_t		num;
	size_t		ttd;
	size_t		tte;
	size_t		tts;
	size_t		ne;
}				t_philoav;

/*
 * 	order	- order of philosopher
 *  die_t	- if philosopher not eat at this time - he will be died
 *  av		- subject var
 */
typedef	struct	s_philoch
{
	size_t					order;
	pthread_t				index;
	pthread_mutex_t			*f_fork;
	pthread_mutex_t			*s_fork;
	size_t					die_t;
	size_t 					start_t;
	size_t					eat_count;
	bool					isdead;
	pthread_mutex_t 		*forks; // only philo order 0
	t_philoav				*av;
}							t_philoch;


/*
 *		init_philo.c
 */
ret_s	init_philo(int ac, const char **argv, t_philoch	**ph);

/*
 *		ft_atoi.c
 */
int		ft_atoi(const char *str);

/*
 * 		sumulation.c
 */
void	*philo(void *philo);

/*
 * 		time.c
 */
size_t	get_time_ms();
void	wait_custom(size_t ms);

/*
 * 		set_fork_to_filo.c
 */
void	set_forks_to_philo(t_philoch **p_ch, int i);

#endif
