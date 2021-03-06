/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:54:32 by rledrin           #+#    #+#             */
/*   Updated: 2020/11/19 13:54:32 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_params
{
	int				number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	*prot;
	size_t			number_of_eat;
	struct timeval	*time_start;

}					t_param;

typedef struct		s_fork
{
	pthread_mutex_t	*fork;
	size_t			last_num;
}					t_fork;

typedef struct		s_philo
{
	char			nb[20];
	size_t			num;
	int				*end;
	size_t			*nb_eat;
	pthread_t		*thread;
	pthread_t		*monitor;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct timeval	*time_last_meal;

}					t_philo;

typedef struct		s_one
{
	t_param			*param;
	t_philo			*philo;

}					t_one;

#endif
