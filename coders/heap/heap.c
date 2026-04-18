
#include "../codexion.h"

void	init_heap(t_dongle *dongle)
{
	dongle->heap[0] = NULL;
	dongle->heap[1] = NULL;
}

bool	has_heap_priority(t_dongle *dongle, t_coder *coder)
{
	return (dongle->heap[0]->id == coder->id);
}

void	heap_pop(t_dongle *dongle)
{
	dongle->heap[0] = dongle->heap[1];
	dongle->heap[1] = NULL;
}

void	heap_push(t_dongle *dongle, t_coder *coder, t_manager *mng)
{
	printf("[DBG] pushed coder_%d to dongle_%d\n", coder->id, dongle->id);
	if (dongle->heap[0] == NULL)
	{
		dongle->heap[0] = coder;
		printf("OH");
		return ;
	}
	if (mng->arg->scheduler == 1) // fifo
		dongle->heap[1] = coder;
	else // edf
	{
		if (dongle->heap[0]->burnout_delay <= coder->burnout_delay)
			dongle->heap[1] = coder;
		else
		{
			dongle->heap[1] = dongle->heap[0];
			dongle->heap[0] = coder;
		}
	}
}
