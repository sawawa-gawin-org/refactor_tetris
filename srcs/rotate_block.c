#include "../tetris.h"

//FunctionRS
void	rotate_block(t_shape shape)
{
	t_shape	temp = create_new_block(shape);
	int 	i;
	int		j;
	int		k;
	int		width;

	width = shape.width;
	i = 0;
	while (i < width)
	{
		j = 0;
		k = width - 1;
		while (j < width)
		{
			shape.array[i][j] = temp.array[k][i];
			j++;
			k--;
		}
		i++;
	}
	destroy_old_block(temp);
}
