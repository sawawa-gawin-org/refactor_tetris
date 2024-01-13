#include "tetris.h"

//ブロックの初期状態(種類、落下開始位置)を決定する関数。
t_shape	create_random_block(void)
{
	t_shape	new_shape;

	new_shape = allocate_block(StructsArray[rand() % 7]);
	new_shape.col = rand() % (WIDTH - new_shape.width + 1);
	new_shape.row = 0;
	return (new_shape);
}

//ブロックが回転可能な正方形の空間を作り、引数のブロックを1マスづつ配置する関数
// allocate_block
t_shape	allocate_block(t_shape shape)
{
	t_shape	new_shape;
	int		i, j;

	new_shape = shape;
	new_shape.array = (char **)malloc(new_shape.width * sizeof(char *));
	i = 0;
	while (i < new_shape.width)
	{
		new_shape.array[i] = (char *)malloc(new_shape.width * sizeof(char));
		j = 0;
		while (j < new_shape.width)
		{
			new_shape.array[i][j] = shape.array[i][j];
			j++;
		}
		i++;
	}
	return (new_shape);
}
