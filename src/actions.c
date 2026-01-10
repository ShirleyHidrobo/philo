/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:24:00 by shhidrob          #+#    #+#             */
/*   Updated: 2026/01/10 21:20:31 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*single_philo(void *p)
{
	t_philo	*plo;

	plo = (t_philo *)p;
	pthread_mutex_lock(&plo->args->fork[plo->left_f]);
	printer(plo, GFORK);
	ft_sleeper(plo, plo->args->t_die);
	pthread_mutex_unlock(&plo->args->fork[plo->left_f]);
	pthread_mutex_lock(&plo->args->checks);
	plo->args->fnsh_game = GAME_OVER;
	pthread_mutex_unlock(&plo->args->checks);
	printer(plo, DIED);
	return (NULL);
}

void	grab_fork(t_philo *plo)
{
	if (plo->id_num % 2 == 0)
	{
		pthread_mutex_lock(&plo->args->fork[plo->left_f]);
		printer(plo, GFORK);
		pthread_mutex_lock(&plo->args->fork[plo->right_f]);
		printer(plo, GFORK);
	}
	else
	{
		pthread_mutex_lock(&plo->args->fork[plo->right_f]);
		printer(plo, GFORK);
		pthread_mutex_lock(&plo->args->fork[plo->left_f]);
		printer(plo, GFORK);
	}
}

void	p_eats(t_philo *plo)
{
	pthread_mutex_lock(&plo->args->checks);
	if (plo->args->fnsh_game == GAME_OVER)
	{
		pthread_mutex_unlock(&plo->args->checks);
		return ;
	}
	pthread_mutex_unlock(&plo->args->checks);
	grab_fork(plo);
	printer(plo, EATING);
	pthread_mutex_lock(&plo->args->checks);
	plo->last_meal = timestamp(plo->args);
	pthread_mutex_unlock(&plo->args->checks);
	ft_sleeper(plo, plo->args->t_eat);
	pthread_mutex_lock(&plo->args->checks);
	plo->meal_eaten++;
	pthread_mutex_unlock(&plo->args->checks);
	pthread_mutex_unlock(&plo->args->fork[plo->left_f]);
	pthread_mutex_unlock(&plo->args->fork[plo->right_f]);
}

void	p_thinks(t_philo *plo)
{
	pthread_mutex_lock(&plo->args->checks);
	if (plo->args->fnsh_game == GAME_OVER)
	{
		pthread_mutex_unlock(&plo->args->checks);
		return ;
	}
	pthread_mutex_unlock(&plo->args->checks);
	printer(plo, THINKING);
}

void	p_sleeps(t_philo *plo)
{
	pthread_mutex_lock(&plo->args->checks);
	if (plo->args->fnsh_game == GAME_OVER)
	{
		pthread_mutex_unlock(&plo->args->checks);
		return ;
	}
	pthread_mutex_unlock(&plo->args->checks);
	printer(plo, SLEEPING);
	ft_sleeper(plo, plo->args->t_sleep);
}
