
#include "../codexion.h"

void	init_heap(t_dongle *dongle)
{
	dongle->heap[0] = NULL;
	dongle->heap[1] = NULL;
}

void	heap_push(t_dongle *dongle, t_coder *coder, t_manager *mng)
{
	if (dongle->heap[0] == NULL)
	{
		dongle->heap[0] = coder;
		return ;
	}
	if (mng->arg->scheduler == 1) // fifo
		dongle->heap[1] = coder;
	else // edf
	{
		if (dongle->heap[0]->burnout_delay < coder->burnout_delay)
			dongle->heap[1] = coder;
		else
		{
			dongle->heap[1] = dongle->heap[0];
			dongle->heap[0] = coder;
		}
	}
}
