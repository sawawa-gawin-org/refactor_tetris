#include "../tetris.h"

//FunctionCS 
t_shape	create_new_block(t_shape shape)
{
	t_shape	new_shape = shape;
	char	**copyshape = shape.array;
	int		i, j;

	new_shape.array = (char **)malloc(new_shape.width * sizeof(char *));
	i = 0;
	while (i < new_shape.width)
	{
		new_shape.array[i] = (char *)malloc(new_shape.width * sizeof(char));
		j = 0;
		while (j < new_shape.width)
		{
			new_shape.array[i][j] = copyshape[i][j];
			j++;
		}
		i++;
	}
	return (new_shape);
}


