/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:23:55 by shhidrob          #+#    #+#             */
/*   Updated: 2026/01/10 21:27:08 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_start(t_store *store)
{
	int	i;

	if (store->n_philo == 1)
		single_philo(store->philo[0]);
	else
	{
		i = -1;
		while (++i < store->n_philo)
		{
			pthread_create(&store->philo[i]->thd, NULL,
				routine, store->philo[i]);
		}
		while (store->fnsh_game == GAME_RUNNING)
			monitor(store);
	}
}

void	*routine(void *val)
{
	t_philo	*plo;
	t_store	*store;

	plo = (t_philo *)val;
	store = plo->args;
	if (plo->id_num % 2)
		usleep(1500);
	while (1)
	{
		pthread_mutex_lock(&store->checks);
		if (store->fnsh_game == GAME_OVER)
		{
			pthread_mutex_unlock(&store->checks);
			break ;
		}
		pthread_mutex_unlock(&store->checks);
		p_eats(plo);
		p_sleeps(plo);
		p_thinks(plo);
	}
	return (NULL);
}

void	monitor(t_store *store)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < store->n_philo)
		{
			check_life(store->philo[i]);
			i++;
		}
		meal_limit_check(store);
		pthread_mutex_lock(&store->checks);
		if (store->fnsh_game == GAME_OVER)
		{
			pthread_mutex_unlock(&store->checks);
			return ;
		}
		pthread_mutex_unlock(&store->checks);
		usleep(1000);
	}
}

void	check_life(t_philo *plo)
{
	pthread_mutex_lock(&plo->args->checks);
	if (plo->args->fnsh_game == GAME_OVER)
	{
		pthread_mutex_unlock(&plo->args->checks);
		return ;
	}
	if ((timestamp(plo->args) - plo->last_meal) >= plo->args->t_die)
	{
		plo->args->fnsh_game = GAME_OVER;
		pthread_mutex_unlock(&plo->args->checks);
		printer(plo, DIED);
		return ;
	}
	pthread_mutex_unlock(&plo->args->checks);
}

void	meal_limit_check(t_store *store)
{
	int	meal_nbr;

	meal_nbr = 0;
	if (store->meal_limit > 0)
	{
		while (meal_nbr < store->n_philo)
		{
			pthread_mutex_lock(&store->checks);
			if (store->philo[meal_nbr]->meal_eaten < store->meal_limit)
			{
				pthread_mutex_unlock(&store->checks);
				break ;
			}
			pthread_mutex_unlock(&store->checks);
			meal_nbr++;
		}
		if (meal_nbr == store->n_philo)
		{
			pthread_mutex_lock(&store->checks);
			store->fnsh_game = GAME_OVER;
			pthread_mutex_unlock(&store->checks);
		}
	}
}
