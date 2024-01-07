#include "../tetris.h"

//FunctionCS 
t_shape	create_new_block(t_shape shape)
{
	t_shape	new_shape = shape;
	char	**copyshape = shape.array;
	int		i;
	int		j;

	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
	for(i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
	}
	return new_shape;
}
