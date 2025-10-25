/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:11:26 by shhidrob          #+#    #+#             */
/*   Updated: 2025/10/25 19:14:24 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_store *store;

	if(validate_args(ac, av) != 0)
		return(FAILURE);
	store = (t_store *)ft_calloc(1, sizeof(t_store));
	if(!store)
		return(FAILURE);
	if(init_start(av, store))
		return(FAILURE);
	philo_start(store);
	philo_destroy(store);
	return(SUCCESS);
}
