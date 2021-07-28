#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include "stdbool.h"
#include "stdio.h"
#include "sys/time.h"
#include <unistd.h>
#include "stdlib.h"
#include <pthread.h>
#include "semaphore.h"
#include <sys/types.h>
#include <signal.h>

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
	int 		ne;
}				t_philoav;

/*
 * 	order	- order of philosopher
 *  die_t	- if philosopher not eat at this time - he will be died
 *  av		- subject var
 */
typedef	struct	s_philoch
{
	size_t					order;
	sem_t					*sem;
	size_t					die_t;
	size_t 					start_t;
	size_t					eat_count;
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
int	philo(void *philo);

/*
 * 		time.c
 */
size_t	get_time_ms();
void	wait_custom(size_t ms);

/*
 * 		set_fork_to_filo.c
 */
void	init_philo_forks(t_philoch **p_ch);


#endif //PHILO_BONUS_H
