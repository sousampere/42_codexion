
#include "../codexion.h"

bool	check_end(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		if (mng->coders[i].nb_compiles != mng->arg->nb_compiles)
			return (false);
	}
	return (true);
}

// bool	check_burnout(t_manager *mng)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < mng->arg->nb_coders)
// 	{
// 		if (mng->coders[i].burnout_delay != mng->arg->nb_compiles)
// 			return (false);
// 	}
// 	return (true);
// }

void	*monitor_routine(void *arg)
{
	t_manager	*mng;

	mng = (t_manager *) arg;
	while (!check_end(mng))
		continue;
	return (NULL);
}

void	start_monitor(t_manager *mng)
{
	pthread_t	thread;

	mng->is_ended = 0;
	pthread_create(&thread, NULL, &monitor_routine, mng);
	pthread_join(thread, NULL);
}
