/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:03:54 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/10 11:10:26 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static int	check_burnout(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->args->nb_coders)
	{
		if (mng->coders[i].time_to_burnout <= get_rel_time(mng))
		{
			printf("%ld %d burned out\n", get_rel_time(mng),
				mng->coders[i].coder_id);
			return (1);
		}
	}
	return (0);
}

static int	all_coders_done(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->args->nb_coders)
		if (mng->coders[i].nb_compiles < mng->args->nb_compiles)
			return (0);
	return (1);
}

void	*monitor_routine(void *manager)
{
	t_manager	*mng;

	mng = (t_manager *)manager;
	while (!all_coders_done(mng))
	{
		if (check_burnout(mng))
		{
			mng->is_burn_out = 1;
			return (NULL);
		}
	}
	mng->is_burn_out = 0;
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
