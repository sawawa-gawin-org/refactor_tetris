#include "tetris.h"

//ブロック(shape.array)を90度右回転させる関数。引数のshapeを更新する。
void	rotate_block(t_shape shape)
{
	t_shape	temp;
	int 	i, j, k;

	temp = allocate_block(shape);
	i = 0;
	while (i < shape.width)
	{
		j = 0;
		k = shape.width - 1;
		while (j < shape.width)
		{
			shape.array[i][j] = temp.array[k][i];
			j++;
			k--;
		}
		i++;
	}
	destroy_block(temp);
}
