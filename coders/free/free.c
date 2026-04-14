

#include "../codexion.h"

void	*free_mng_and_args(t_manager *mng)
{
	free(mng->arg);
	free(mng);
	return (NULL);
}