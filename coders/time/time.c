/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:26:56 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 17:26:58 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	get_rel_time(t_manager *mng)
{
	long	current_time;
	int		rel_time;

	current_time = get_time_in_ms();
	pthread_mutex_lock(&mng->rel_time_mtx);
	rel_time = current_time - mng->start_timestamp;
	pthread_mutex_unlock(&mng->rel_time_mtx);
	return (rel_time);
}
