
#include "../codexion.h"

void	compile(t_coder *coder, t_manager *mng)
{
	coder->left_dongle->cooldown_end = get_rel_time(mng)
		+ mng->arg->dongle_cooldown;
	coder->right_dongle->cooldown_end = get_rel_time(mng)
		+ mng->arg->dongle_cooldown;
	sprint(coder, mng, 2);
	coder->burnout_delay = get_rel_time(mng) + mng->arg->burnout_time;
	usleep(mng->arg->compile_time * 1000);
	coder->nb_compiles += 1;
}

void	debug(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 4);
	usleep(mng->arg->compile_time * 1000);
}

void	refactor(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 3);
	usleep(mng->arg->refactor_time * 1000);
}

bool	can_pick_dongles(t_coder *coder, t_manager *mng)
{
	bool	status;

	pthread_mutex_lock(&coder->left_dongle->mutex);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	if (coder->left_dongle->is_used == 0
		&& coder->right_dongle->is_used == 0
		&& has_heap_priority(coder->left_dongle, coder, mng)
		&& coder->left_dongle->cooldown_end <= get_rel_time(mng)
		&& coder->right_dongle->cooldown_end <= get_rel_time(mng))
	{
		coder->left_dongle->is_used = true;
		coder->right_dongle->is_used = true;
		status = true;
	}
	else
	{
		// printf("%d %d %d %d %d\n", 
		// 	coder->left_dongle->is_used == 0,
		// 	coder->right_dongle->is_used == 0,
		// 	has_heap_priority(coder->left_dongle, coder, mng),
		// 	coder->left_dongle->cooldown_end <= get_rel_time(mng),
		// 	coder->right_dongle->cooldown_end <= get_rel_time(mng));
		status = false;
	}
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	return (status);
}

void	release_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	coder->left_dongle->is_used = false;
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	coder->right_dongle->is_used = false;
	pthread_mutex_unlock(&coder->right_dongle->mutex);
}

void	*routine(void *arg)
{
	t_routine_arg	*args;

	args = (t_routine_arg *) arg;
	// printf("%d woke up 😈.\n", args->coder->id);
	while (args->coder->nb_compiles < args->manager->arg->nb_compiles)
	{
		// printf("coder %d has priority of %d\n", args->coder->id, can_pick_dongles(args->coder, args->manager));
		if (can_pick_dongles(args->coder, args->manager))
		{
			heap_rm(args->coder->left_dongle, args->coder);
			heap_rm(args->coder->right_dongle, args->coder);
			sprint(args->coder, args->manager, 1);
			compile(args->coder, args->manager);
			release_dongles(args->coder);
			debug(args->coder, args->manager);
			refactor(args->coder, args->manager);
			heap_push(args->coder->left_dongle, args->coder, args->manager);
			heap_push(args->coder->right_dongle, args->coder, args->manager);
		}
	}
	return (NULL);
}

void	start_simulation(t_manager *mng)
{
	int				i;

	i = -1;
	mng->coders_threads = malloc(sizeof(pthread_t) * mng->arg->nb_coders);
	mng->routine_args = malloc(sizeof(t_routine_arg) * mng->arg->nb_coders);
	while (++i < mng->arg->nb_coders)
	{
		mng->routine_args[i].manager = mng;
		mng->routine_args[i].coder = &mng->coders[i];
		pthread_create(&mng->coders_threads[i],
			NULL, &routine, &mng->routine_args[i]);
	}
}
