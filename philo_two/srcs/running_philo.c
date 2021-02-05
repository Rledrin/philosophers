/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:54:52 by rledrin           #+#    #+#             */
/*   Updated: 2020/11/19 13:54:52 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/functions.h"

int	g_someone_died = 0;
t_param	*g_param = NULL;

static inline int	status(char *nb, char *msg, int len)
{
	char			str[1024];
	int				i;
	long long		time;
	struct timeval	now;

	sem_wait(g_param->prot);
	gettimeofday(&now, NULL);
	time = ((now.tv_sec - g_param->time_start->tv_sec) * 1000 +
		(now.tv_usec - g_param->time_start->tv_usec) * 0.001);
	if (g_someone_died && msg[len - 2] != 'd')
	{
		sem_post(g_param->prot);
		return (0);
	}
	i = print_nbr((size_t)time, str);
	str[i++] = '\t';
	while (*nb)
		str[i++] = *(nb++);
	while (len-- > 0)
		str[i++] = *(msg++);
	write(1, str, i);
	sem_post(g_param->prot);
	return (0);
}

static inline int	eating(t_philo *philo, t_param *param, struct timeval *now)
{
	sem_wait(param->grab);
	sem_wait(param->forks);
	gettimeofday(now, NULL);
	status(philo->nb, "\t\thas taken a fork\n", 19);
	sem_wait(param->forks);
	gettimeofday(now, NULL);
	status(philo->nb, "\t\thas taken a fork\n", 19);
	gettimeofday(now, NULL);
	status(philo->nb, "\t\tis eating\n", 12);
	gettimeofday(philo->time_last_meal, NULL);
	sem_wait(param->prot);
	++(*philo->nb_eat);
	sem_post(param->prot);
	fixed_usleep(param->time_to_eat * 1000);
	sem_post(param->forks);
	sem_post(param->forks);
	sem_post(param->grab);
	return ((*philo->nb_eat >= param->number_of_eat) ? 9 : 0);
}

static inline void	*call_eat(t_one *fake_one)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if ((eating(fake_one->philo, fake_one->param, &now) ||
			sem_wait(fake_one->param->prot) || g_someone_died ||
		*fake_one->philo->end) && !gettimeofday(&now, NULL))
		return (!sem_post(fake_one->param->prot) ? NULL : 0);
	sem_post(fake_one->param->prot);
	status(fake_one->philo->nb, "\t\tis sleeping\n", 14);
	fixed_usleep(fake_one->param->time_to_sleep * 1000);
	return (fake_one);
}

void				*living_philo(void *tmp_fake)
{
	t_one			*fake_one;
	struct timeval	now;

	fake_one = (t_one*)tmp_fake;
	g_param = fake_one->param;
	while (1)
	{
		if (!call_eat(fake_one))
			return (NULL);
		sem_wait(fake_one->param->prot);
		if (g_someone_died || *fake_one->philo->end)
			return (!(sem_post(fake_one->param->prot)) ? NULL : 0);
		sem_post(fake_one->param->prot);
		gettimeofday(&now, NULL);
		status(fake_one->philo->nb, "\t\tis thinking\n", 14);
		sem_wait(fake_one->param->prot);
		if (g_someone_died || *fake_one->philo->end)
			return (!(sem_post(fake_one->param->prot)) ? NULL : 0);
		sem_post(fake_one->param->prot);
	}
}

void				*true_monitor_philo(t_one *fake_one)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (((((now.tv_sec - fake_one->philo->time_last_meal->tv_sec) *
		1000 + (now.tv_usec - fake_one->philo->time_last_meal->tv_usec) *
		0.001)) > fake_one->param->time_to_die) && !g_someone_died)
	{
		sem_wait(fake_one->param->prot);
		g_someone_died = 1;
		sem_post(fake_one->param->prot);
		status(fake_one->philo->nb, "\t\tdied\n", 7);
		return (NULL);
	}
	sem_wait(fake_one->param->prot);
	if ((fake_one->param->number_of_eat > 0 &&
		*fake_one->philo->nb_eat >= fake_one->param->number_of_eat))
	{
		sem_post(fake_one->param->prot);
		return ((!(*fake_one->philo->end = 1) ? NULL : 0));
	}
	sem_post(fake_one->param->prot);
	fixed_usleep(500);
	return (fake_one);
}
