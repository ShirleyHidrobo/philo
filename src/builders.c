/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builders.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:06:01 by shhidrob          #+#    #+#             */
/*   Updated: 2025/11/18 17:58:39 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	validate_args(int ac, char **av)
{
	if (ac > 5 && ac < 6)
	{
		printf("%s\n", ERR_ARGC_NUM);
		printf("%s\n", ERR_ARG_EXPECT);
		return (FAILURE);
	}
	if (check_digit(av))
	{
		printf("%s", ERR_INV_ARG);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_overflow(t_store *store, char **av)
{
	if (store->n_philo > 200 || store->n_philo <= 0)
		return (FAILURE);
	if (store->t_die < 60 || store->t_eat < 60 || store->t_sleep < 60)
		return (FAILURE);
	if (av[5])
	{
		store->meal_limit = ft_atoi(av[5]);
		if (store->meal_limit < 0)
			return (FAILURE);
	}
	else
		store->meal_limit = false;
	return (SUCCESS);
}

int	init_start(char **av, t_store *store)
{
	int	i;

	i = -1;
	store->error = false;
	store->fnsh_game = false;
	store->end_meal = 0;
	store->n_philo = ft_atoi(av[1]);
	store->t_die = ft_atoi(av[2]);
	store->t_eat = ft_atoi(av[3]);
	store->t_sleep = ft_atoi(av[4]);
	if (check_overflow(store, av))
	{
		printf("%s", ERR_INV_ARG);
		return (free(store), 1);
	}
	store->philo = malloc(store->n_philo * (sizeof(t_philo *)));
	store->fork = malloc(store->n_philo * (sizeof(pthread_mutex_t)));
	pthread_mutex_init(&store->checks, NULL);
	while (++i < store->n_philo)
		pthread_mutex_init(&store->fork[i], NULL);
	init_philos(store);
	store->t_start = timestart();
	return (SUCCESS);
}

void	init_philos(t_store *store)
{
	int	i;

	i = 0;
	while (i < store->n_philo)
	{
		store->philo[i] = malloc(sizeof(t_philo));
		store->philo[i]->id_num = i + 1;
		store->philo[i]->meal_eaten = 0;
		store->philo[i]->last_meal = 0;
		store->philo[i]->left_f = i;
		store->philo[i]->right_f = (i + 1) % store->n_philo;
		if (store->philo[i]->id_num % 2 == 0)
		{
			store->philo[i]->left_f = (i + 1) % store->n_philo;
			store->philo[i]->right_f = i;
		}
		store->philo[i]->args = store;
		i++;
	}
}

void	philo_destroy(t_store *store)
{
	int	i;

	i = 0;
	if (store->n_philo > 1)
	{
		while (i < store->n_philo)
			pthread_join(store->philo[i++]->thd, NULL);
	}
	i = 0;
	while (i < store->n_philo)
		pthread_mutex_destroy(&store->fork[i++]);
	pthread_mutex_destroy(&store->checks);
	i = 0;
	while (i < store->n_philo)
	{
		free(store->philo[i++]);
	}
	free(store->philo);
	free(store->fork);
	free(store);
}
