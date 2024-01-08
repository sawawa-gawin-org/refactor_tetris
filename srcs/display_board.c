#include "../tetris.h"

static void	get_mino_overlay(char Buffer[R][C]);

//FunctionPT
void	display_board(void)
{
	char	Buffer[R][C];

	memcpy(Buffer, Table, R * C * sizeof(char));
	get_mino_overlay(Buffer);
	clear();
	display_title("42 Tetris\n", printw);
	display_array(Buffer, printw);
	display_score(final, printw);
}

static void	get_mino_overlay(char Buffer[R][C])
{
	int		i;
	int		j;

	i = 0;
	while (i < current.width)
	{
		j = 0;
		while (j < current.width)
		{
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] += current.array[i][j];
			j++;
		}
		i++;
	}
}
