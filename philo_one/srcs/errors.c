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

static void		ft_puterr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		write(STDERR_FILENO, &(str[i++]), 1);
}

int				errors(int err)
{
	if (err == TOO_MANY_ARGS)
		ft_puterr("Error: Wrong number of arguments\n");
	else if (err == WRONG_ARG)
		ft_puterr("Error: Wrong argument\n");
	else if (err == ERROR_MALLOC)
		ft_puterr("Error: malloc error\n");
	else if (err == ERROR_MUTEX)
		ft_puterr("Error: mutex error\n");
	else if (err == ERROR_PTHREAD)
		ft_puterr("Error: pthread error\n");
	else if (err == ERROR_SLEEP)
		ft_puterr("Error: usleep error\n");
	else if (err == ERROR_TIMEOFDAY)
		ft_puterr("Error: gettimeofday error\n");
	return (err);
}
