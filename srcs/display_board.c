#include "../tetris.h"

//FunctionPT
void	display_board(void)
{
	char	Buffer[R][C];
	int		i;
	int		j;

	memcpy(Buffer, Table, R * C * sizeof(char));
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
	clear();
	i = 0;
	while (i < C - 9)
	{
		printw(" ");
		i++;
	}
	printw("42 Tetris\n");
	display_array(Buffer, printw);
	printw("\nScore: %d\n", final);
}
