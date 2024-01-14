#include "tetris.h"

//最上部もしくは底辺に達した時にTRUE、達しておらずゲーム続行可能であればFALSE
int	is_reaching_bottom(t_shape shape)
{
	char	**array;
	int		i, j;

	array = shape.array;
	i = 0;
	while (i < shape.size)
	{
		j = 0;
		while (j < shape.size)
		{
			if((shape.col + j < 0 || shape.col + j >= WIDTH || shape.row + i >= HEIGHT))
			{
				if(array[i][j])
					return (TRUE);
			}
			else if (Table[shape.row + i][shape.col + j] && array[i][j])
				return (TRUE);
			j++;
		}
		i++;
	}
	return (FALSE);
}
