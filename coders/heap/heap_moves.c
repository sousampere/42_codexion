#include "../codexion.h"

void	heap_init(t_dongle	*dongle)
{
	dongle->heap[0] = malloc(sizeof(t_coder));
	dongle->heap[1] = malloc(sizeof(t_coder));
	dongle->heap[0] = NULL;
	dongle->heap[1] = NULL;
}

void	heap_pop(t_dongle	*dongle)
{
	if (dongle->heap[0] == NULL)
		return ;
	// heap 0 non null
	if (dongle->heap[1] == NULL)
	{
		dongle->heap[0] = NULL;
		return ;
	}
	dongle->heap[0] = dongle->heap[1];
	dongle->heap[1] = NULL;
	return ;
}

void	heap_push(t_dongle *dongle, t_coder *coder, t_manager *mng)
{
	if (dongle->heap[0] == NULL)
	{
		dongle->heap[0] = coder;
		return ;
	}
	if (strcmp(mng->args->scheduler, "fifo") == 0)
		dongle->heap[1] = coder;
	else if (dongle->heap[0]->time_to_burnout < coder->time_to_burnout)
		dongle->heap[1] = coder;
	else
	{
		dongle->heap[1] = dongle->heap[0];
		dongle->heap[0] = coder;
	}

}

void	heap_rm(t_coder *coder)
{
	// printf("%d\n", coder->left_dongle->heap[0]->coder_id);
	sleep(1);
	if (coder->left_dongle->heap[0]->coder_id == coder->coder_id)
		heap_pop(coder->left_dongle);
	if (coder->right_dongle->heap[0]->coder_id == coder->coder_id)
		heap_pop(coder->right_dongle);

}

bool	is_first_in_queue(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->mutex);
	if (dongle->heap[0] == NULL)
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (true);
	}
	if (dongle->heap[0]->coder_id == coder->coder_id)
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (true);
	}
	pthread_mutex_unlock(&dongle->mutex);
	return (false);
}