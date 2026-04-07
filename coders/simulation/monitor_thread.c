/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:45:37 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/07 17:55:05 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	monitor_burnout(t_manager	*mng)
{
	int		i;

	i = 0;
	while (i < mng->args->nb_coders)
	{
		if (mng->coders[i].time_to_burnout < get_time_in_ms())
		{
			print("%d %i burned out", get_time_in_ms(), mng->coders[i].coder_id);
			free_all(mng);
			return (0);
		}
		i++;
		if (i == mng->args->nb_coders)
			i = 0;
	}
}
