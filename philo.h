/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:42:37 by shhidrob          #+#    #+#             */
/*   Updated: 2025/10/25 19:10:35 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

# define SUCESS 0
# define FAILURE -42

# define ERROR1 "Invalid argument detected"
# define ERROR2 "The program expects 4-5 Numeric Args"
# define ERROR3 "Ex: ./philo [num of philo] [time 2 die] [time 2 eat]"
# define GFORK	"Grabbed a fork"
# define DIED	"died"
# define EATING	"is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"

//typedef struct s_philo t_philo;
//typedef struct s_store t_store;

typedef struct	s_philo
{
	int	meal_eaten;
	int	id_num;
	pthread_t	thd;
	long long	last_meal;
	int		right_f;
	int		left_f;
	t_store	*args;
}		t_philo;

typedef struct s_store
{
	int	error;
	bool	fnsh_game;
	int	end_meal;
	long long	t_start;
	long long	t_eat;
	long long	t_die;
	long long	t_sleep;
	int	n_philo;
	int	meal_limit;
	t_philo	*philo;
	pthread_mutex_t	checks;
	pthread_mutex_t *fork;
}		t_store;

int	check_digit(char **str);
int	ft_atoi(const char *str);
int validate_args(int ac, char **av);
int ft_atoi(const char *str);
int	check_overflow(t_store *store, char **av);
long long	timestart(void);
long long	timestamp(t_store *store);
int	init_start(char **av, t_store *store);
void	*ft_calloc(size_t count, size_t size);
void	init_philos(t_store *store);
void	philo_start(t_store *store);
void	*routine(void *val);
void	*single_philo(void *p);
void	printer(t_philo *plo, char *str);
void	ft_sleeper(t_philo *plo, int t_2_wait);
void	philo_destroy(t_store *store);
void	monitor(t_store *store);
void	p_eats(t_philo *plo);
void	p_thinks(t_philo *plo);
void	p_sleeps(t_philo *plo);
void	check_life(t_philo *plo);
void	grab_fork(t_philo *plo);
void	meal_limit_check(t_store *store);
void	printeright_f(t_philo *plo);

#endif

