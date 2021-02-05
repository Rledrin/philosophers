/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:54:55 by rledrin           #+#    #+#             */
/*   Updated: 2020/11/19 13:54:55 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/functions.h"

void			fixed_usleep(unsigned int usec)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
			((size_t)(step.tv_usec - start.tv_usec))) > usec)
			break ;
	}
}

void			*m(size_t size)
{
	void		*ptr;

	ptr = NULL;
	if (!(ptr = malloc(size)))
		return (ptr);
	memset(ptr, 0, size);
	return (ptr);
}

int				ft_atos(char *str, size_t *nb)
{
	if (*str == '\0')
		return (-1);
	*nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		*nb = 10 * *nb + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	return (0);
}

int				print_nbr(size_t nbr, char *str)
{
	size_t			nnbr;
	long long int	pow;
	char			c;
	int				i;

	i = 0;
	pow = 10;
	nnbr = nbr;
	while (nnbr /= 10)
		pow *= 10;
	while ((pow /= 10))
	{
		c = ((nbr / pow) % 10 + '0');
		str[i++] = c;
	}
	return (i);
}
