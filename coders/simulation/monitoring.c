/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:03:54 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/11 14:38:56 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	*monitor_routine(void *manager)
{
	int			i;
	int			is_every_coder_done;
	t_manager	*mng;

	i = -1;
	mng = (t_manager *)manager;
	is_every_coder_done = 1;
	i = -1;
	while (++i < mng->args->nb_coders)
	{
		// printf("checking coder %d\n", i);
		if (mng->coders[i].time_to_burnout <= get_rel_time(mng))
		{
			printf("%ld %d burned out\n", get_rel_time(mng), mng->coders[i].coder_id);
			printf("%ld %d burned out with date to %d\n", get_rel_time(mng), mng->coders[i].coder_id, mng->coders[i].time_to_burnout);
			mng->is_burn_out = 1;
			return (NULL);
		}
		if (mng->coders[i].nb_compiles < mng->args->nb_compiles)
			is_every_coder_done = 0;
		if (i == mng->args->nb_coders - 1)
		{
			if (is_every_coder_done == 1)
			{
				mng->is_burn_out = 0;
				return (NULL);
			}
			i = -1;
			is_every_coder_done = 1;
		}
	}
	return (NULL);
}

int	monitor_burnout(t_manager *mng)
{
	pthread_t	monitoring;

	pthread_create(&monitoring, NULL, &monitor_routine, mng);
	pthread_join(monitoring, NULL);
	if (mng->is_burn_out == 0)
		printf("== end of simulation ==\n");
	return (mng->is_burn_out);
}
