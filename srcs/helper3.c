/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:01:21 by aalseri           #+#    #+#             */
/*   Updated: 2022/08/29 23:06:58 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_fork_norme(t_philo *philo, int fork)
{
	philo->main->forks_a[fork] = philo->id;
	pthread_mutex_unlock(&philo->main->forks[fork]);
}
