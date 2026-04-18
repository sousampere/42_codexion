
#include "codexion.h"

int main(int argc, char **argv)
{
	t_manager	*mng;

	mng = init_manager(argc, argv);
	if (!mng)
		return (printf("Invalid argument.\n"), 1);
	// int i = -1;
	// while (++i < mng->arg->nb_coders)
	// {
	// 	printf("-----\nright %d\n", mng->coders[i].left_dongle->id);
	// 	printf("coder %d\n", mng->coders[i].left_dongle->id);
	// 	printf("left %d\n", mng->coders[i].right_dongle->id);
	// 	printf("left priority -> %d, %d\n", mng->coders[i].left_dongle->heap[0]->id, mng->coders[i].left_dongle->heap[1]->id);
	// 	printf("right priority -> %d, %d\n", mng->coders[i].right_dongle->heap[0]->id, mng->coders[i].right_dongle->heap[1]->id);
	// }
	start_simulation(mng);
	start_monitor(mng);
	free_all(mng);
}
