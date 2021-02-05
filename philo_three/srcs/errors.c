/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:54:42 by rledrin           #+#    #+#             */
/*   Updated: 2020/11/19 13:54:42 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/functions.h"

static int		ft_puterr(char *str)
{
	size_t	i;
	ssize_t	ret;

	ret = 0;
	i = 0;
	while (str[i])
		ret = write(STDERR_FILENO, &(str[i++]), 1);
	return (ret);
}

int				errors(int err)
{
	if (err == TOO_MANY_ARGS)
		ft_puterr("Error: Wrong number of arguments\n");
	else if (err == WRONG_ARG)
		ft_puterr("Error: Wrong argument\n");
	else if (err == ERROR_MALLOC)
		ft_puterr("Error: Malloc error\n");
	else if (err == ERROR_SEM)
		ft_puterr("Error: Semaphore error\n");
	else if (err == ERROR_PTHREAD)
		ft_puterr("Error: Pthread error\n");
	else if (err == ERROR_SLEEP)
		ft_puterr("Error: Usleep error\n");
	else if (err == ERROR_TIMEOFDAY)
		ft_puterr("Error: Gettimeofday error\n");
	return (err);
}
