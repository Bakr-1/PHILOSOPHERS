/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:34:58 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/01 20:13:02 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

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
		(*m)->philosopher[i].forks[i] = i;
		if (((*m)->n_philo - 1) == i)
			(*m)->philosopher[i].left_fork = 0;
		else
			(*m)->philosopher[i].left_fork = i + 1;
		(*m)->philosopher[i].right_fork = i;
		if (i % 2)
			ft_swap(&(*m)->philosopher[i].left_fork, &(*m)->philosopher[i].right_fork);
		(*m)->philosopher[i].meals = 0;
		(*m)->philosopher[i].eating = 0;
		(*m)->philosopher[i].forks[i] = -1;
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
