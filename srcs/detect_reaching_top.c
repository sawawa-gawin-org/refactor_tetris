#include "tetris.h"

//FunctionCP
int	detect_reaching_top(t_shape shape)
{
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= C || shape.row+i >= R)){
				if(array[i][j])
					return (0);
			}
			else if(Table[shape.row+i][shape.col+j] && array[i][j])
				return (0);
		}
	}
	return (1);
}
