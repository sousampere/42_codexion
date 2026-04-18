

#include "../codexion.h"

void	*free_mng_and_args(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		free(mng->coders[i].left_dongle->heap[0]);
		free(mng->coders[i].left_dongle->heap[1]);
		free(mng->coders[i].left_dongle);
		// free(mng->coders[i]);
	}
	free(mng->coders_threads);
	free(mng->arg);
	free(mng);
	return (NULL);
}

void	free_all(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		pthread_mutex_destroy(&mng->coders[i].left_dongle->mutex);
		// free(mng->coders[i].left_dongle->heap[0]);
		// free(mng->coders[i].left_dongle->heap[1]);
	}
	free(mng->coders);
	free(mng->dongles);
	free(mng->arg);
	free(mng->coders_threads);
	free(mng->routine_args);
	pthread_mutex_destroy(&mng->printf_mtx);
	free(mng);
}
