
#include "../codexion.h"

void	compile(t_coder *coder, t_manager *mng)
{
	coder->left_dongle->cooldown_end = get_rel_time(mng)
		+ mng->arg->dongle_cooldown;
	coder->right_dongle->cooldown_end = get_rel_time(mng)
		+ mng->arg->dongle_cooldown;
	sprint(coder, mng, 2);
	sleep(2);
	coder->burnout_delay = get_rel_time(mng) + mng->arg->burnout_time;
	usleep(mng->arg->compile_time * 1000);
	coder->nb_compiles += 1;
	printf("coder %d has now a burnout of %d\n", coder->id, coder->burnout_delay);
}

bool	can_pick_dongles(t_coder *coder, t_manager *mng)
{
	bool	status;

	pthread_mutex_lock(&coder->left_dongle->mutex);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	if (coder->left_dongle->is_used == 0
		&& coder->right_dongle->is_used == 0
		&& has_heap_priority(coder->left_dongle, coder)
		&& coder->left_dongle->cooldown_end <= get_rel_time(mng)
		&& coder->right_dongle->cooldown_end <= get_rel_time(mng))
	{
		// pick dongles
		coder->left_dongle->is_used = true;
		coder->right_dongle->is_used = true;
		status = true;
	} else
		status = false;
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	return (status);
}

void	*routine(void *arg)
{
	t_routine_arg	*args;

	args = (t_routine_arg *) arg;
	printf("%d woke up 😈.\n", args->coder->id);
	if (can_pick_dongles(args->coder, args->manager))
	{
		sprint(args->coder, args->manager, 1);
		compile(args->coder, args->manager);
	}
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
