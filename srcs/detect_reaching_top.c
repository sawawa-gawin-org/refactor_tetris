#include "../tetris.h"

//FunctionCP
int	detect_reaching_top(t_shape shape)
{
	char **array = shape.array;
	int i, j;

	i = 0;
	while (i < shape.width)
	{
		j = 0;
		while (j < shape.width)
		{
			if((shape.col + j < 0 || shape.col + j >= C || shape.row + i >= R))
			{
				if(array[i][j])
					return (0);
			}
			else if (Table[shape.row + i][shape.col + j] && array[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
