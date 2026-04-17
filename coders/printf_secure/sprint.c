
#include "../codexion.h"

void	sprint(t_coder *coder, t_manager *mng, int code)
{
	// printf("Locking printf\n");
	pthread_mutex_lock(&mng->printf_mtx);
	// printf("Printf locked\n");
	if (code == 1)
	{
		printf("\033[0;33m%d %d has taken a dongle.\033[0m\n",
			get_rel_time(mng), coder->id);
		printf("\033[0;33m%d %d has taken a dongle.\033[0m\n",
			get_rel_time(mng), coder->id);
	}
	if (code == 2)
		printf("\033[0;36m%d %d is compiling.\033[0m\n",
			get_rel_time(mng), coder->id);
	if (code == 3)
		printf("\033[0;34m%d %d is refactoring.\033[0m\n",
			get_rel_time(mng), coder->id);
	if (code == 4)
		printf("\033[0;35m%d %d is debugging.\033[0m\n",
			get_rel_time(mng), coder->id);
	if (code == 5)
		printf("\033[0;31m%d %d burned out.\033[0m\n",
			get_rel_time(mng), coder->id);
	pthread_mutex_unlock(&mng->printf_mtx);
}
