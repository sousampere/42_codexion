
#include "../codexion.h"

int	get_burnout(t_manager *mng, t_coder *coder)
{
	int	delay;

	pthread_mutex_lock(&mng->gobal_mtx);
	delay = coder->burnout_delay;
	pthread_mutex_unlock(&mng->gobal_mtx);
	return (delay);
}
