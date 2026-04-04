/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:52:38 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/04 20:28:05 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	*routine(void *coder)
{
	t_coder	*current_coder;

	current_coder = (t_coder *) coder;
	printf("coder %d coding...\n", current_coder->coder_id);
	printf("coder %d has left_dongle of time %ld...\n", current_coder->coder_id, current_coder->left_dongle->cooldown);
	printf("coder %d has right_dongle of time %ld...\n", current_coder->coder_id, current_coder->right_dongle->cooldown);
	return (NULL);
}

// int	start_simulation(t_args *args)
// {
// 	t_coder		*coders;
// 	pthread_t	*threads;
// 	int			i;

// 	if (!coders)
// 		return (printf("Failed to allocate memory.\n"), 1);
// 	threads = malloc(sizeof(pthread_t) * args->nb_coders);
// 	i = 0;
// 	give_dongles(coders, args);
// 	while (i < args->nb_coders)
// 	{
// 		pthread_create(&threads[i], NULL, &routine, &coders[i]);
// 		pthread_join(threads[i], NULL);
// 		i++;
// 	}
// 	free(threads);
// 	free(coders);
// 	free(args);
// 	return (0);
// }