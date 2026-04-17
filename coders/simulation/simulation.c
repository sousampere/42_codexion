
#include "../codexion.h"


void	*routine(void *arg)
{
	t_routine_arg	*args;

	args = (t_routine_arg *) arg;
	printf("%d woke up 😈.\n", args->coder->id);
	return (NULL);
}

void	start_simulation(t_manager *mng)
{
	int				i;
	pthread_t		*threads;
	t_routine_arg	*args;

	i = -1;
	threads = malloc(sizeof(pthread_t) * mng->arg->nb_coders);
	args = malloc(sizeof(t_routine_arg) * mng->arg->nb_coders);
	while (++i < mng->arg->nb_coders)
	{
		args[i].manager = mng;
		args[i].coder = &mng->coders[i];
		pthread_create(&threads[i], NULL, &routine, &args[i]);
	}
}
