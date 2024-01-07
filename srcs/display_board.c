#include "../tetris.h"

//FunctionPT
void	display_board(void)
{
	char	Buffer[R][C] = {0};
	int		i;
	int		j;

	i = 0;
	while (i < current.width)
	{
		j = 0;
		while (j < current.width)
		{
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] = current.array[i][j];
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
	i = 0;
	while (i < R)
	{
		j = 0;
		while (j < C)
		{
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
			j++;
		}
		printw("\n");
		i++;
	}
	printw("\nScore: %d\n", final);
}
