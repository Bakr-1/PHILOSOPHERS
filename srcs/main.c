/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:14:45 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/02 15:55:01 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo(t_main *m)
{
	size_t		i;

	i = 0;
	m->start_time = get_time();
	while (i < m->n_philo)
	{
		if (pthread_create(&(m)->philosopher[i].thread_id, NULL, &action,
				&m->philosopher[i]))
			ft_putendl_fd("Thread ERROR", 2, 1);
		usleep(10);
		i++;
	}
	i = 0;
	while (i < m->n_philo)
		pthread_join(m->philosopher[i++].thread_id, NULL);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
		ft_putendl_fd("Usage: ./philo [nop][ttd][tte][tts][notte]", 2, 1);
	init1(&main, ac, av);
	philo(&main);
	destroy_thex(&main);
	return (0);
}
