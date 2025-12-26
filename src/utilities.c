/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:31:08 by shhidrob          #+#    #+#             */
/*   Updated: 2025/11/18 18:05:57 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// FIX: la lógica anterior estaba invertida, ahora devuelve 1 si es dígito, 0 si no
static int	ft_isdigit(int ascii_nbr)
{
	if (ascii_nbr >= '0' && ascii_nbr <= '9')
		return (1);
	return (0);
}

// FIX: la función ahora recorre todos los argumentos y caracteres, y valida correctamente
int	check_digit(char **str)
{
	int i = 1; // asume que str[0] es el nombre del programa
	int j;

	while (str[i])
	{
		j = 0;
		if (str[i][j] == '-') // permite negativos solo si es el primer caracter
			j++;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (FAILURE); // retorna FAILURE si encuentra un caracter no numérico
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

// FIX: Devuelve -1 en caso de error y chequea overflow correctamente
int	ft_atoi(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)res);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*ptr;

	// FIX: previous logic failed for count == 0, should check count != 0 && size > SIZE_MAX / count
	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	for (size_t i = 0; i < total; i++)
		ptr[i] = '\0';
	return (ptr);
}

// FIX: Bloquea el mutex antes de comprobar fnsh_game para evitar condiciones de carrera
void	printer(t_philo *plo, char *str)
{
	pthread_mutex_lock(&plo->args->checks);
	if (plo->args->fnsh_game == false)
		printf("%lld %d %s\n", timestamp(plo->args), plo->id_num, str);
	pthread_mutex_unlock(&plo->args->checks);
}
