/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:21:00 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/02 11:32:51 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	pick_fork1(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->main->forks_mute[philo->left_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->main->forks_mute[philo->left_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->main->forks_mute[philo->right_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->main->forks_mute[philo->left_fork]);
		pthread_mutex_unlock(&philo->main->forks_mute[philo->right_fork]);
		return (1);
	}
	return (0);
}

int	pick_fork(t_philo *philo)
{
	while (1)
	{
		if (pick_fork1(philo))
			return (1);
		if (is_dead(philo))
		{
			pthread_mutex_unlock(&philo->main->forks_mute[philo->left_fork]);
			pthread_mutex_unlock(&philo->main->forks_mute[philo->right_fork]);
			return (1);
		}
		if (philo->main->forks_array[philo->left_fork] != (int)philo->id
			&& philo->main->forks_array[philo->right_fork] != (int)philo->id)
		{
			display_info(philo, get_time(), TAKING_FORK);
			display_info(philo, get_time(), TAKING_FORK);
			if (eating(philo))
				return (unlock_forks(philo));
			break ;
		}
		pthread_mutex_unlock(&philo->main->forks_mute[philo->right_fork]);
		pthread_mutex_unlock(&philo->main->forks_mute[philo->left_fork]);
	}
	return (0);
}

int	eating2(t_philo *philo)
{
	display_info(philo, philo->last_meal, END);
	philo->main->end++;
	if (philo->main->end >= philo->main->n_philo)
		return (1);
	return (1);
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
	philo->main->forks_array[philo->left_fork] = philo->id;
	philo->main->forks_array[philo->right_fork] = philo->id;
	pthread_mutex_unlock(&philo->main->forks_mute[philo->right_fork]);
	pthread_mutex_unlock(&philo->main->forks_mute[philo->left_fork]);
	if (philo->main->n_meals > 0 && philo->meals >= philo->main->n_meals)
		return (eating2(philo));
	return (0);
}

void	*action(void *v)
{
	t_philo	*philo;

	philo = (t_philo *)v;
	philo->last_meal = get_time();
	philo->ttlive = philo->last_meal + philo->main->ttdie;
	if (philo->main->n_philo == 1)
		while (1)
			if (is_dead(philo))
				return (NULL);
	while (1)
	{
		if (pick_fork(philo))
			return (NULL);
		display_info(philo, philo->last_meal + philo->main->tteat, SLEEPING);
		ft_usleep(philo->main->ttsleep);
		display_info(philo, get_time(), THINKING);
		if (is_dead(philo))
			return (NULL);
	}
	return (NULL);
}
