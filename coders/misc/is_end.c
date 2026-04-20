
#include "../codexion.h"

bool	is_ended(t_manager *mng)
{
	bool	status;

	pthread_mutex_lock(&mng->gobal_mtx);
	status = mng->is_ended;
	pthread_mutex_unlock(&mng->gobal_mtx);
	return (status);
}