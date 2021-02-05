/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:54:28 by rledrin           #+#    #+#             */
/*   Updated: 2020/11/19 13:54:28 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>
# include "errors.h"
# include "structs.h"

int			errors(int err);
size_t		ft_strlen(char *str);
int			ft_atos(char *str, size_t *nb);
int			init_philo(t_one *one);
int			philo_start(t_one *one);
void		fixed_usleep(unsigned int usec);
void		*monitor_philo(void *tmp_fake);
void		*living_philo(void *tmp_fake);
void		*true_monitor_philo(t_one *fake_one);
int			print_nbr(size_t nbr, char *str);
void		*m(size_t size);

#endif
