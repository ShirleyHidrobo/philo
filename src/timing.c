/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:58:33 by shhidrob          #+#    #+#             */
/*   Updated: 2026/01/10 21:28:51 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	timestart(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
}

long long	timestamp(t_store *store)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - store->t_start);
}

void	ft_sleeper(t_philo *plo, int t_2_wait)
{
	long long	start;

	start = timestamp(plo->args);
	while ((timestamp(plo->args) - start) < t_2_wait)
		usleep(30);
}
