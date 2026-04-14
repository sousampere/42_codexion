
#include "codexion.h"

int main(int argc, char **argv)
{
	t_manager	*mng;
	(void) argc;
	(void) argv;

	mng = init_manager(argc, argv);
	if (!mng)
		return (printf("Invalid argument.\n"), 1);
	int i = -1;
	while (++i < mng->arg->nb_coders)
	{
		
		printf("-----\nright %d\n", mng->coders[i].left_dongle->id);
		printf("coder %d\n", mng->coders[i].id);
		printf("left %d\n", mng->coders[i].right_dongle->id);
	}

}