/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:54:45 by rledrin           #+#    #+#             */
/*   Updated: 2020/11/19 13:54:45 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/functions.h"

static inline int	philo_start_joins(t_one *one, t_one *tmp_fake)
{
	int				i;

	i = 0;
	while (1)
	{
		if (!true_monitor_philo(&tmp_fake[i++]))
			break ;
		if (i >= one->param->number_of_philosophers)
			i = 0;
		fixed_usleep(1000);
	}
	i = 0;
	while (i < one->param->number_of_philosophers)
	{
		pthread_join(*(one->philo[i++].thread), NULL);
	}
	free(tmp_fake);
	return (0);
}

int					philo_start(t_one *one)
{
	int				i;
	t_one			*tmp_fake;

	i = 0;
	if (!(one->param->time_start = m(sizeof(struct timeval))) ||
		!(tmp_fake = m(sizeof(t_one) *
		one->param->number_of_philosophers)))
		return (ERROR_MALLOC);
	gettimeofday(one->param->time_start, NULL);
	while (i < one->param->number_of_philosophers)
	{
		tmp_fake[i].param = one->param;
		tmp_fake[i].philo = &(one->philo[i]);
		one->philo[i].time_last_meal->tv_sec = one->param->time_start->tv_sec;
		one->philo[i].time_last_meal->tv_usec = one->param->time_start->tv_usec;
		if (pthread_create(one->philo[i].thread, NULL,
			&living_philo, &(tmp_fake[i])))
			return (ERROR_PTHREAD);
		i++;
	}
	return (philo_start_joins(one, tmp_fake));
}

static inline int	malloc_init_philo(t_philo *philo)
{
	if (!(philo->thread = m(sizeof(pthread_t))) ||
		!(philo->time_last_meal = m(sizeof(struct timeval))) ||
		!(philo->nb_eat = m(sizeof(size_t))) ||
		!(philo->end = m(sizeof(int))))
		return (ERROR_MALLOC);
	return (0);
}

int					init_philo(t_one *one)
{
	int				i;

	i = -1;
	if (!(one->philo = m(sizeof(t_philo) *
		one->param->number_of_philosophers)))
		return (ERROR_MALLOC);
	while (++i < one->param->number_of_philosophers)
	{
		if (malloc_init_philo(&(one->philo[i])) < 0)
			return (ERROR_MALLOC);
		one->philo[i].num = i + 1;
		memset(one->philo[i].nb, 0, 4);
		print_nbr(i + 1, one->philo[i].nb);
		*one->philo[i].nb_eat = 0;
		*one->philo[i].end = 0;
	}
	return (0);
}
