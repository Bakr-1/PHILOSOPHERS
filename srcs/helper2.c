/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:19:21 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/02 02:09:31 by aalseri          ###   ########.fr       */
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
	if (*str != '\0')
		return (1);
	return (0);
}

void	display_info(t_philo *philo, size_t timestamp, int action)
{
	static int	flag;

	pthread_mutex_lock(&philo->main->write);
	if (action == TAKING_FORK && !flag)
		printf(GRN"%zu Philo %zu has taken a fork 🍴\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	else if (action == EATING && !flag)
		printf(GRN"%zu Philo %zu is eating 🍝\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	else if (action == SLEEPING && !flag)
		printf(GRN"%zu Philo %zu is sleeping 😴\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	else if (action == THINKING && !flag)
		printf(GRN"%zu Philo %zu is thinking 🤔\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	else if (action == DIED && !flag)
	{
		flag++;
		printf(RED"%zu Philo %zu died 😵\n"RESET,
			timestamp - philo->main->start_time, philo->id + 1);
	}
	else if (action == END && !flag)
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
	pthread_mutex_destroy(&m->extra);
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
		display_info(philo, philo->ttlive, DIED);
		pthread_mutex_unlock(&philo->main->die);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->die);
	return (0);
}
