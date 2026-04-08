/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:59:13 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/08 11:43:33 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

long	get_time_in_ms(void)
{
	// Return the current timestamp in ms
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_rel_time(t_manager *mng)
{
	long	current_time;

	current_time = get_time_in_ms();
	return (current_time - mng->start_timestamp);
}