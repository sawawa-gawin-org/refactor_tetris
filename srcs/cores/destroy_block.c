#include "tetris.h"

//t_shape型の構造体のメンバの2次元配列をfreeする関数
void	destroy_block(t_shape shape)
{
	int	i;

	i = 0;
	while (i < shape.size)
	{
		free(shape.array[i]);
		i++;
	}
	free(shape.array);
}
