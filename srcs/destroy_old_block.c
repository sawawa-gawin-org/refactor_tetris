#include "../tetris.h"

//FunctionDS
void	destroy_old_block(t_shape shape)
{
	int i;
	for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
	}
	free(shape.array);
}
