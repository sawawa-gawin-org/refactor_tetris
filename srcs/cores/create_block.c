#include "tetris.h"

//ブロックの初期状態(種類、落下開始位置)をランダムに決定する関数
t_shape	create_random_block(const t_shape *tetriminos)
{
	t_shape	new_shape;

	new_shape = duplicate_block(tetriminos[rand() % 7]);
	new_shape.col = rand() % (WIDTH - new_shape.size + 1);
	new_shape.row = 0;
	return (new_shape);
}

//mallocで割り当てた2次元配列に引数のブロックを入れる関数
t_shape	duplicate_block(t_shape shape)
{
	t_shape	new_shape;
	int		i, j;

	new_shape = shape;
	new_shape.array = (char **)malloc(new_shape.size * sizeof(char *));
	i = 0;
	while (i < new_shape.size)
	{
		new_shape.array[i] = (char *)malloc(new_shape.size * sizeof(char));
		j = 0;
		while (j < new_shape.size)
		{
			new_shape.array[i][j] = shape.array[i][j];
			j++;
		}
		i++;
	}
	return (new_shape);
}
