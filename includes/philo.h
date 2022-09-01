/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:18:51 by aalseri           #+#    #+#             */
/*   Updated: 2022/09/01 20:13:23 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

# define TRUE 1
# define FALSE 0

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	END,
}				t_action;

typedef struct s_fk
{
	int				*lf;
	int				*rf;
}					t_fk;

typedef struct s_philo
{
	pthread_t		thread_id;
	size_t			id;
	int				left_fork;
	int				right_fork;
	size_t			forks[250];
	size_t			meals;
	size_t			eating;
	size_t			last_meal;
	size_t			ttlive;
	size_t			avaliable[250];
	size_t			has_eaten;
	struct s_main	*main;
}					t_philo;

typedef struct s_main
{
	size_t			st;
	size_t			n_philo;
	size_t			tteat;
	size_t			ttdie;
	size_t			ttsleep;
	size_t			n_meals;
	size_t			end;
	int				forks_a[250];
	size_t			done;
	t_philo			philosopher[250];
	unsigned int	philo_dead;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	write;
	pthread_mutex_t	die;
	pthread_mutex_t	extra;
}					t_main;

void	ft_putendl_fd(char *s, int fd, int i);
int		ft_atoi_chk(const char *string, size_t *dst);
size_t	get_time(void);
void	ft_usleep(size_t ms);
void	philo(t_main *m);
void	*action(void *v);
void	display_info(t_philo *philo, size_t timestamp, int action);
void	destroy_thex(t_main *m);
int		is_dead(t_philo *philo);
void	pick_fork_norme(t_philo *philo, int fork);
void	init1(t_main *m, int ac, char **av);
int		eating(t_philo *philo);

#endif