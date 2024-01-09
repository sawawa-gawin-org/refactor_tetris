#include "../tetris.h"

//FunctionDS
void	destroy_old_block(t_shape shape)
{
	int	i;

	i = 0;
	while (i < shape.width)
	{
		free(shape.array[i]);
		i++;
	}
	free(shape.array);
}
