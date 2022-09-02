/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:19:21 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/02 14:53:00 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi_chk(const char *str, size_t *dst)
{
	if (*str == '\0')
		return (1);
	*dst = 0;
	while (*str && *str >= '0' && *str <= '9')
		*dst = *dst * 10 + (*str++ - '0');
	if (*dst > 2147483647)
		return (1);
	if (*str != '\0')
		return (1);
	return (0);
}

void	display_info(t_philo *philo, size_t timestamp, int action)
{
	pthread_mutex_lock(&philo->main->write);
	if (action == TAKING_FORK && !philo->main->flag)
		printf(GRN"%zu Philo %zu has taken a fork 🍴\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	else if (action == EATING && !philo->main->flag)
		printf(GRN"%zu Philo %zu is eating 🍝\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	else if (action == SLEEPING && !philo->main->flag)
		printf(GRN"%zu Philo %zu is sleeping 😴\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	else if (action == THINKING && !philo->main->flag)
		printf(GRN"%zu Philo %zu is thinking 🤔\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	else if (action == END && !philo->main->flag)
		printf(BLU"%zu Philo %zu has finished his meals 😋\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->main->write);
}

void	destroy_thex(t_main *m)
{
	size_t	i;

	i = 0;
	while (i < m->n_philo)
		pthread_mutex_destroy(&m->forks_mute[i++]);
	pthread_mutex_destroy(&m->write);
	pthread_mutex_destroy(&m->die);
}

void	print_death(t_philo *philo  ,size_t timestamp )
{
	pthread_mutex_lock(&philo->main->write);
	if (!philo->main->flag)
	{
		philo->main->flag++;
		printf(RED"%zu Philo %zu died 😵\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->main->write);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->die);
	if (philo->main->philo_dead)
	{
		pthread_mutex_unlock(&philo->main->die);
		return (1);
	}
	if (!(philo->main->philo_dead) && !philo->eating
		&& get_time() > philo->ttlive)
	{
		philo->main->philo_dead = 1;
		print_death(philo, get_time());
		pthread_mutex_unlock(&philo->main->die);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->die);
	return (0);

}

/***
 * 1. 5 200 100 100 - simulation continues after death - death printed a little late
2. Make sure to check for death while he's perfprming an action (in case he dies while doing the action)
3. timings are not synchornized sometimes
Eg. 20 200 1000000 100
 * */