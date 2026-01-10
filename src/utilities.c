/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:31:08 by shhidrob          #+#    #+#             */
/*   Updated: 2026/01/10 21:39:22 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isdigit(int ascii_nbr)
{
	return (ascii_nbr >= '0' && ascii_nbr <= '9');
}

int	check_digit(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		return (FAILURE);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	if (res > INT_MAX)
		return (FAILURE);
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = count * size;
	if (size >= SIZE_MAX / count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < j)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

void	printer(t_philo *plo, t_state state)
{
	long long	time;

	pthread_mutex_lock(&plo->args->print);
	time = timestamp(plo->args);
	if (state == DIED)
		return (printf("%lld %d died\n", timestamp(plo->args), plo->id_num),
			pthread_mutex_unlock(&plo->args->print), (void)0);
	pthread_mutex_lock(&plo->args->checks);
	if (plo->args->fnsh_game == GAME_OVER)
		return (pthread_mutex_unlock(&plo->args->checks),
			pthread_mutex_unlock(&plo->args->print), (void)0);
	pthread_mutex_unlock(&plo->args->checks);
	if (state == GFORK)
		printf("%lld %d has taken a fork\n", time, plo->id_num);
	else if (state == EATING)
		printf("%lld %d is eating\n", time, plo->id_num);
	else if (state == SLEEPING)
		printf("%lld %d is sleeping\n", time, plo->id_num);
	else if (state == THINKING)
		printf("%lld %d is thinking\n", time, plo->id_num);
	pthread_mutex_unlock(&plo->args->print);
}
