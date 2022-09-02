/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:33:11 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/02 11:35:33 by aalseri          ###   ########.fr       */
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

void	ft_putendl_fd(char *s, int fd, int i)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	if (i)
		exit (1);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t duration)
{
	long long	start_sleep;

	start_sleep = get_time();
	while (get_time() - start_sleep < duration)
		usleep(duration);
}
