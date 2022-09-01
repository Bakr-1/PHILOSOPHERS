/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:21:00 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/01 20:01:47 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_fork_norme(t_philo *philo, int fork)
{
	philo->main->forks_a[fork] = philo->id;
	pthread_mutex_unlock(&philo->main->forks[fork]);
}

int	pick_fork1(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->main->forks[philo->left_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->main->forks[philo->left_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->main->forks[philo->right_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->main->forks[philo->right_fork]);
		pthread_mutex_unlock(philo->main->forks[philo->left_fork]);
		return (1);
	}
	return (0);
	// int		i;
	// int		fork;

	// i = 0;
	// while (i < 2)
	// {
	// 	if (is_dead(philo))
	// 		return (1);
	// 	if (i == 0 && philo->id % 2 == 0)
	// 		fork = philo->fork.rf;
	// 	else if (i ==  1 &&  philo->id % 2 == 0)
	// 		fork = philo->fork.lf;
	// 	else if (i == 0 && philo->id % 2 == 1)
	// 		fork = philo->fork.lf;
	// 	else if (i ==  1 &&  philo->id % 2 == 1)
	// 		fork = philo->fork.rf;
	// 	printf("left fork %p  right fork %p\n", &(philo->fork.rf), &(philo->fork.lf));
	// 	pthread_mutex_lock(&philo->main->forks[fork]);
		// if (philo->main->forks_a[fork] != (int)philo->id && !philo->avaliable[fork])
	// 	{
	// 		philo->avaliable[fork] = 1;
	// 		philo->main->forks_a[fork] = philo->id;
	// 		pthread_mutex_unlock(&philo->main->forks[fork]);
	// 		if (is_dead(philo))
	// 			return (1);
	// 		i++;
	// 	}
	// 	else
	// 		pthread_mutex_unlock(&philo->main->forks[fork]);
	// }
	// return (0);
}

int	pick_fork(t_philo *philo)
{
	while (1)
	{
		if (pick_fork1(philo))
			return (1);
		if (is_dead(philo))
		{
			pthread_mutex_unlock(philo->main->forks[philo->right_fork]);
			pthread_mutex_unlock(philo->main->forks[philo->left_fork]);
			return (1);
		}
		if (philo->forks[philo->left_fork] != philo->id
			&& philo->forks[philo->right_fork] != philo->id)
		{
			display_info(philo, get_time(), TAKING_FORK);
			eating(philo);
			break ;
		}
		pthread_mutex_unlock(philo->main->forks[philo->right_fork]);
		pthread_mutex_unlock(philo->main->forks[philo->left_fork]);
		if (is_dead(philo))
			return (1);
	}
}

int	eating(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	philo->eating = 1;
	philo->last_meal = get_time();
	display_info(philo, philo->last_meal, EATING);
	ft_usleep(philo->main->tteat);
	philo->ttlive = philo->last_meal + philo->main->ttdie;
	philo->eating = 0;
	philo->meals += 1;
	philo->forks[philo->left_fork] = philo->id;
	philo->forks[philo->right_fork] = philo->id;
	pthread_mutex_unlock(philo->main->forks[philo->right_fork]);
	pthread_mutex_unlock(philo->main->forks[philo->left_fork]);
	if (philo->main->n_meals > 0 && philo->meals >= philo->main->n_meals)
	{
		display_info(philo, philo->last_meal, END);
		pthread_mutex_lock(&philo->main->extra);
		philo->main->end++;
		if (philo->main->end >= philo->main->n_philo)
		{
			pthread_mutex_unlock(&philo->main->extra);
			return (1);
		}
		pthread_mutex_unlock(&philo->main->extra);
		return (1);
	}
	return (0);
}

int	removing_fork(t_philo *philo)
{
	// pthread_mutex_lock(&philo->main->forks[philo->fork.lf]);
	// philo->main->forks_a[philo->fork.lf] = 0;
	// pthread_mutex_unlock(&philo->main->forks[philo->fork.lf]);
	// pthread_mutex_lock(&philo->main->forks[philo->fork.rf]);
	// philo->main->forks_a[philo->fork.rf] = 0;
	// pthread_mutex_unlock(&philo->main->forks[philo->fork.rf]);
	//philo->avaliable[philo->fork.lf] = 0;
	//philo->avaliable[philo->fork.rf] = 0;
	if (is_dead(philo))
		return (1);
	display_info(philo, philo->last_meal + philo->main->tteat, SLEEPING);
	ft_usleep(philo->main->ttsleep);
	if (is_dead(philo))
		return (1);
	display_info(philo, philo->last_meal + philo->main->tteat
		+ philo->main->ttsleep, THINKING);
	return (0);
}

void	*action(void *v)
{
	t_philo	*philo;

	philo = (t_philo *)v;
	if (philo->main->n_philo != 1)
	{
		if (philo->id % 2 == 0)
			usleep(50);
	}
	philo->last_meal = get_time();
	philo->ttlive = philo->last_meal + philo->main->ttdie;
	while (1)
	{
		if (pick_fork(philo) || eating(philo) || removing_fork(philo))
			break ;
	}
	return (NULL);
}
