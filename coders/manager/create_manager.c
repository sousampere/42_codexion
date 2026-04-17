
#include "../codexion.h"

// Overflow, negative, non-integer and non-digit protection
int	is_invalid_value(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
	{
		if (string[i] < '0' || string[i] > '9')
			return (1);
	}
	if (strlen(string) > 10)
		return (1);
	if (strlen(string) >= 9 && string[9] >= '8')
	{
		string[9] = '\0';
		if (atoi(string) >= 214748364)
			return (1);
	}
	return (0);
}

int	validate_args(char **argv)
{
	int	i;

	i = 0;
	while (++i)
	{
		if (i == 8)
			break ;
		if (is_invalid_value(argv[i]))
			return (0);
	}
	return (1);
}

t_args	*get_args(int argc, char **argv)
{
	t_args	*args_ptr;

	if (!validate_args(argv))
		return (NULL);
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		return (NULL);
	if (argc != 9)
		return (NULL);
	args_ptr = malloc(sizeof(t_args));
	if (!args_ptr)
		return (NULL);
	args_ptr->nb_coders = atoi(argv[1]);
	args_ptr->burnout_time = atoi(argv[2]);
	args_ptr->compile_time = atoi(argv[3]);
	args_ptr->debug_time = atoi(argv[4]);
	args_ptr->refactor_time = atoi(argv[5]);
	args_ptr->nb_compiles = atoi(argv[6]);
	args_ptr->dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8], "fifo") == 0)
		args_ptr->scheduler = 1;
	if (strcmp(argv[8], "edf") == 0)
		args_ptr->scheduler = 0;
	return (args_ptr);
}

t_coder	*init_coders(t_manager *mng)
{
	t_coder	*coders;
	int		i;

	coders = malloc(sizeof(t_coder) * mng->arg->nb_coders);
	if (!coders)
		return (NULL);
	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		coders[i].id = i + 1;
		coders[i].burnout_delay = mng->arg->burnout_time;
		coders[i].nb_compiles = 0;
	}
	return (coders);
}

void	init_dongles(t_manager *mng)
{
	t_dongle	*dongles;
	int			i;

	dongles = malloc(sizeof(t_dongle) * mng->arg->nb_coders);
	if (!dongles)
		return ;
	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		mng->coders[i % mng->arg->nb_coders].left_dongle = &dongles[i % mng->arg->nb_coders];
		mng->coders[i % mng->arg->nb_coders].right_dongle = &dongles[(i + 1) % mng->arg->nb_coders];
		mng->coders[i % mng->arg->nb_coders].left_dongle->id = i + 1;
		mng->coders[i].left_dongle->cooldown_end = 0;
		mng->coders->left_dongle->heap[0] = malloc(sizeof(t_coder));
		mng->coders->left_dongle->heap[1] = malloc(sizeof(t_coder));
		pthread_mutex_init(&mng->coders[i].left_dongle->mutex, NULL);
	}
	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		init_heap(mng->coders[i].left_dongle);
		heap_push(mng->coders[i % mng->arg->nb_coders].left_dongle, &mng->coders[i % mng->arg->nb_coders], mng);
		heap_push(mng->coders[i % mng->arg->nb_coders].left_dongle, &mng->coders[(i + 1) % mng->arg->nb_coders], mng);
	}
}

t_manager	*init_manager(int argc, char **argv)
{
	t_manager	*mng;

	mng = malloc(sizeof(t_manager));
	if (!mng)
		return (NULL);
	mng->arg = get_args(argc, argv);
	if (!mng->arg)
		return (NULL);
	mng->coders = init_coders(mng);
	if (!mng->coders)
		return (free_mng_and_args(mng));
	init_dongles(mng);
	mng->start_timestamp = get_time_in_ms();
	return (mng);
}
