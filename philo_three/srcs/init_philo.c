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

static inline void	*philo_start_joins(void *fone)
{
	int				i;
	t_one			*one;

	one = fone;
	i = 0;
	while (i < one->param->number_of_philosophers)
	{
		kill(one->param->pid[i++], SIGKILL);
	}
	return (NULL);
}

static inline int	waitmain(t_one *one, t_one *tmp_fake)
{
	int				i;
	int				ret;
	int				status;

	i = 0;
	free(tmp_fake);
	ret = 1;
	while (1)
	{
		waitpid(one->param->pid[i], &status, WNOHANG | WUNTRACED);
		if (WIFEXITED(status))
		{
			if ((ret = WEXITSTATUS(status)) == 1)
			{
				philo_start_joins(one);
				sem_post(one->param->prot);
				return (0);
			}
		}
		++i;
		if (i >= one->param->number_of_philosophers)
			i = 0;
		fixed_usleep(1000);
	}
	return (0);
}

int					philo_start(t_one *one)
{
	int				i;
	t_one			*tmp_f;

	i = -1;
	if (!(one->param->time_start = m(sizeof(struct timeval))) ||
		!(tmp_f = m(sizeof(t_one) * one->param->number_of_philosophers)))
		return (ERROR_MALLOC);
	gettimeofday(one->param->time_start, NULL);
	while (++i < one->param->number_of_philosophers)
	{
		tmp_f[i].param = one->param;
		tmp_f[i].philo = &(one->philo[i]);
		one->philo[i].time_last_meal->tv_sec = one->param->time_start->tv_sec;
		one->philo[i].time_last_meal->tv_usec = one->param->time_start->tv_usec;
		if ((one->param->pid[i] = fork()) == 0)
		{
			if (pthread_create(one->philo[i].monitor, NULL,
				&monitor_philo, &tmp_f[i]) ||
				pthread_detach(*one->philo[i].monitor))
				return (ERROR_PTHREAD);
			living_philo(&tmp_f[i]);
		}
	}
	return (waitmain(one, tmp_f));
}

static inline int	malloc_init_philo(t_philo *philo)
{
	if (!(philo->monitor = m(sizeof(pthread_t))) ||
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
		one->param->number_of_philosophers)) ||
		!(one->param->waitproc = m(sizeof(pthread_t))) ||
		!(one->param->pid = m(sizeof(pid_t) *
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
