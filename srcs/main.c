/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:14:45 by aalseri           #+#    #+#             */
/*   Updated: 2022/08/30 11:00:07 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init3(t_main ***m)
{
	size_t	i;

	i = 0;
	while (i < (**m)->n_philo)
		pthread_mutex_init(&(**m)->forks[i++], NULL);
	pthread_mutex_init(&(**m)->write, NULL);
	pthread_mutex_init(&(**m)->die, NULL);
	pthread_mutex_init(&(**m)->extra, NULL);
}

void	init2(t_main **m)
{
	size_t	i;

	i = 0;
	memset((*m)->forks_a, -1, sizeof(int) * ((*m)->n_philo));
	while (i < (*m)->n_philo)
	{
		(*m)->philosopher[i].id = i;
		(*m)->philosopher[i].fork.lf = i;
		(*m)->philosopher[i].fork.rf = (i + 1) % (*m)->n_philo;
		(*m)->philosopher[i].meals = 0;
		(*m)->philosopher[i].eating = 0;
		(*m)->philosopher[i].main = *m;
		i++;
	}
	init3(&m);
}

void	init1(t_main *m, int ac, char **av)
{
	if (ft_atoi_chk(av[1], &m->n_philo) || m->n_philo == 0
		|| ft_atoi_chk(av[2], &m->ttdie) || m->ttdie == 0
		|| ft_atoi_chk(av[3], &m->tteat) || m->tteat == 0
		|| ft_atoi_chk(av[4], &m->ttsleep) || m->ttsleep == 0)
		return (ft_putendl_fd("Invalid input", 2, 1));
	if (ac == 6 && (ft_atoi_chk(av[5], &m->n_meals)
			|| m->n_meals == 0))
		return (ft_putendl_fd("Invalid input", 2, 1));
	if (ac == 5)
		m->n_meals = -1;
	m->philo_dead = FALSE;
	m->end = 0;
	init2(&m);
}

void	philo(t_main *m)
{
	size_t		i;

	i = 0;
	m->st = get_time();
	while (i < m->n_philo)
	{
		if (pthread_create(&(m)->philosopher[i].thread_id, NULL, &action,
				&m->philosopher[i]))
			ft_putendl_fd("Thread ERROR", 2, 1);
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
