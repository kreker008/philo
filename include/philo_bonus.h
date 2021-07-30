#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "stdbool.h"
# include "stdio.h"
# include "sys/time.h"
# include <unistd.h>
# include "stdlib.h"
# include <pthread.h>
# include "semaphore.h"
# include <sys/types.h>
# include <signal.h>

# define RET_S		int
# define DEATH_FLAG	-2

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
	sem_t					*print_sem;
	size_t					die_t;
	size_t 					start_t;
	size_t					eat_count;
	t_philoav				*av;
}							t_philoch;

/*
 *		init_philo.c
 */
RET_S	init_philo(int ac, const char **argv, t_philoch	**ph);


/*
 *		libft_func.c
 */
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);

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
RET_S	init_philo_sem(t_philoch **p_ch);

/*
 * 		write_func.c
 */
RET_S	write_func(size_t time, size_t order, char *string, t_philoch *ph,
					int ret);

#endif //PHILO_BONUS_H
