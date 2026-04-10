/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:32:36 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/10 08:50:26 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	free_all(t_manager *manager)
{
	int	i;

	i = -1;
	while (++i < manager->args->nb_coders)
		pthread_mutex_destroy(&manager->coders[i].left_dongle->mutex);
	free(manager->dongles);
	free(manager->coders);
	free(manager->args);
	free(manager);
}
