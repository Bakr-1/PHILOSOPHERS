/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:19:21 by aalseri           #+#    #+#             */
/*   Updated: 2022/08/29 01:10:09 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi_chk(const char *string, size_t *dst)
{
	if (*string == '\0')
		return (1);
	*dst = 0;
	while (*string && *string >= '0' && *string <= '9')
		*dst = *dst * 10 + (*string++ - '0');
	if (*string != '\0')
		return (1);
	return (0);
}

void	display_info(t_philo *philo, size_t timestamp, int action)
{
	pthread_mutex_lock(&philo->main->write);
	if (action == TAKING_FORK)
		printf(GRN"%zu Philo %zu has taken a fork 🍴\n",
			timestamp - philo->main->st, philo->id + 1);
	else if (action == EATING)
		printf("%zu Philo %zu is eating 🍝\n",
			timestamp - philo->main->st, philo->id + 1);
	else if (action == SLEEPING)
		printf("%zu Philo %zu is sleeping 😴\n",
			timestamp - philo->main->st, philo->id + 1);
	else if (action == THINKING)
		printf("%zu Philo %zu is thinking 🤔\n",
			timestamp - philo->main->st, philo->id + 1);
	else if (action == DIED)
		printf(RED"%zu Philo %zu died 😵\n",
			timestamp - philo->main->st, philo->id + 1);
	else if (action == END)
		printf(BLU"%zu Philo %zu has finished his meals 😋\n",
			timestamp - philo->main->st, philo->id + 1);
	pthread_mutex_unlock(&philo->main->write);
}

void	free_my_boys(t_main *m)
{
	size_t	k;

	k = 0;
	while (k < m->n_philo)
		pthread_mutex_destroy(&m->forks[k++]);
	pthread_mutex_destroy(&m->write);
	pthread_mutex_destroy(&m->die);
	free(m->forks);
	free(m->philosopher);
	free(m->forks_a);
}
