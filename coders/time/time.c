
#include "../codexion.h"

long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	get_rel_time(t_manager *mng)
{
	long	current_time;

	current_time = get_time_in_ms();
	return (current_time - mng->start_timestamp);
}
