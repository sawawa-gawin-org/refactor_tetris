#include "tetris.h"

//何かしらに接地した場合TRUE、中空に存在&&ゲーム続行可能ならばFALSE
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
			else if (g_table[shape.row + i][shape.col + j] && array[i][j])
				return (TRUE);
			j++;
		}
		i++;
	}
	return (FALSE);
}
