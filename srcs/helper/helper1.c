/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:33:11 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/12 20:32:00 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ((void)str);
	while (str[i])
		ft_putchar_fd(str[i++], fd);
}

int	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	return (1);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t duration, t_philo *philo)
{
	size_t	start_sleep;
	size_t	test;

	start_sleep = get_time();
	test = get_time() - start_sleep;
	while (test < duration)
	{
		test = get_time() - start_sleep;
		if (test > philo->ttlive - start_sleep)
			break ;
		usleep(10);
	}
}
