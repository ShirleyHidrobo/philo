/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:23:55 by shhidrob          #+#    #+#             */
/*   Updated: 2025/11/18 18:02:20 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_start(t_store *store)
{
	int i;

	if (store->n_philo == 1)
		single_philo(store->philo[0]);
	else
	{
		i = 0;
		while (i < store->n_philo)
		{
			pthread_create(&store->philo[i]->thd, NULL, routine, store->philo[i]);
			i++;
		}
		while (store->fnsh_game == false)
			monitor(store);
	}
}

void	*routine(void *val)
{
	t_philo	*plo;
	t_store	*store;

	plo = (t_philo *)val;
	store = plo->args;
	while (1)
	{
		pthread_mutex_lock(&store->checks);
		if (store->fnsh_game == true)
		{
			pthread_mutex_unlock(&store->checks);
			return (NULL); // Termina el hilo correctamente si fnsh_game es true
		}
		pthread_mutex_unlock(&store->checks);
		if (store->meal_limit > 0 && plo->meal_eaten >= store->meal_limit)
			return (NULL); // Termina el hilo si alcanzó el límite de comidas
		p_eats(plo);
		p_sleeps(plo);
		p_thinks(plo);
	}
	// Código muerto, nunca se ejecuta
	return (NULL);
}

void	monitor(t_store *store)
{
	int i;

	i = 0;
	while (i < store->n_philo)
	{
		check_life(store->philo[i]);
		meal_limit_check(store);
		usleep(500);
		i++;
	}
}

void	check_life(t_philo *plo)
{
	long now;
	long last;

	pthread_mutex_lock(&plo->args->checks);
	now = timestamp(plo->args);
	last = plo->last_meal;
	if ((now - last) >= plo->args->t_die && !plo->args->fnsh_game)
	{
		plo->args->fnsh_game = true;
		pthread_mutex_unlock(&plo->args->checks);
		printer(plo, DIED);
		return;
	}
	pthread_mutex_unlock(&plo->args->checks);
}

void	meal_limit_check(t_store *store)
{
	int meal_nbr = 0;
	// FIX: Solo termina si meal_limit > 0
	if (store->meal_limit <= 0)
		return;
	while (meal_nbr < store->n_philo)
	{
		pthread_mutex_lock(&store->checks);
		if (store->philo[meal_nbr]->meal_eaten < store->meal_limit)
		{
			pthread_mutex_unlock(&store->checks);
			break;
		}
		pthread_mutex_unlock(&store->checks);
		meal_nbr++;
	}
	if (meal_nbr == store->n_philo)
	{
		pthread_mutex_lock(&store->checks);
		store->fnsh_game = true;
		pthread_mutex_unlock(&store->checks);
	}
}
