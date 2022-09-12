/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:14:45 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/12 20:30:23 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo(t_main *m)
{
	size_t		i;

	i = 0;
	m->start_time = get_time();
	while (i < m->n_philo)
	{
		if (pthread_create(&(m)->philosopher[i].thread_id, NULL, &action,
				&m->philosopher[i]))
			return (ft_putendl_fd("Thread ERROR", 2));
		usleep(10);
		i++;
	}
	i = 0;
	while (i < m->n_philo)
		pthread_join(m->philosopher[i++].thread_id, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
		return (ft_putendl_fd("Usage: ./philo [nop][ttd][tte][tts][notte]", 2));
	if (init1(&main, ac, av))
		return (1);
	if (philo(&main))
		return (1);
	destroy_thex(&main);
	return (0);
}
