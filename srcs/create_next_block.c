#include "tetris.h"

//ブロックの初期状態(種類、落下開始位置)を決定する関数。
t_shape	create_next_block(void)
{
	t_shape	new_shape;

	new_shape = create_new_block(StructsArray[rand() % 7]);
	new_shape.col = rand() % (WIDTH - new_shape.width + 1);
	new_shape.row = 0;
	return (new_shape);
}
