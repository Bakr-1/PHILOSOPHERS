/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:14:45 by aalseri           #+#    #+#             */
/*   Updated: 2022/08/29 01:00:39 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init3(t_main ***m)
{
	size_t	i;

	i = 0;
	(**m)->forks = malloc(sizeof(pthread_mutex_t) * (**m)->n_philo);
	if (!(**m)->forks)
		ft_putendl_fd("malloc failed 2", 2, 1);
	while (i < (**m)->n_philo)
		pthread_mutex_init(&(**m)->forks[i++], NULL);
	pthread_mutex_init(&(**m)->write, NULL);
	pthread_mutex_init(&(**m)->die, NULL);
}

void	init2(t_main **m)
{
	size_t	i;

	i = 0;
	(*m)->philosopher = malloc(sizeof(t_philo) * ((*m)->n_philo));
	if (!(*m)->philosopher)
		return (ft_putendl_fd("malloc failed 1", 2, 1));
	(*m)->forks_a = malloc(sizeof(int) * ((*m)->n_philo + 1));
	if (!(*m)->forks_a)
		return (ft_putendl_fd("malloc failed 1", 2, 1));
	memset((*m)->forks_a, '\0', sizeof(int) * ((*m)->n_philo));
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
	m->end = 0;
	init2(&m);
}

void	philo(t_main *m)
{
	pthread_t	thread;
	size_t		i;

	i = 0;
	pthread_mutex_lock(&m->die);
	m->st = get_time();
	while (i < m->n_philo)
	{
		if (pthread_create(&thread, NULL, &action, &m->philosopher[i]))
			ft_putendl_fd("Thread ERROR", 2, 1);
		pthread_detach(thread);
		i++;
	}
	pthread_mutex_lock(&m->die);
	pthread_mutex_unlock(&m->die);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
		ft_putendl_fd("Usage: ./philo [nop][ttd][tte][tts][notte]", 2, 1);
	init1(&main, ac, av);
	philo(&main);
	free_my_boys(&main);
	return (0);
}
