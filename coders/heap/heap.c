
#include "../codexion.h"

void	init_heap(t_dongle *dongle)
{
	dongle->heap[0] = NULL;
	dongle->heap[1] = NULL;
}

bool	will_deadlock(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		if (mng->coders[i].left_dongle->heap[0] == NULL)
			return (true);
		if (mng->coders[i].left_dongle->heap[0]->id == mng->coders[i].id)
			return (false);
	}
	return (true);
}

bool	has_heap_priority(t_dongle *dongle, t_coder *coder, t_manager *mng)
{
	if (dongle->heap[0] == NULL)
		return (true);
	if (will_deadlock(mng))
		return (true);
	return (dongle->heap[0]->id == coder->id);
}

void	heap_pop(t_dongle *dongle)
{
	dongle->heap[0] = dongle->heap[1];
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
		if (dongle->heap[0]->burnout_delay <= coder->burnout_delay)
			dongle->heap[1] = coder;
		else
		{
			dongle->heap[1] = dongle->heap[0];
			dongle->heap[0] = coder;
		}
	}
}

void	heap_rm(t_dongle *dongle, t_coder *coder)
{
	if (dongle->heap[0] == NULL)
		return ;
	else if (dongle->heap[0]->id == coder->id)
	{
		dongle->heap[0] = dongle->heap[1];
		dongle->heap[1] = NULL;
	}
	else if (dongle->heap[1] != NULL && dongle->heap[1]->id == coder->id)
		dongle->heap[1] = NULL;
}
