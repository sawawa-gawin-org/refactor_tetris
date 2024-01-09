#include "../tetris.h"

static void	get_mino_overlay(char buffer[HEIGHT][WIDTH]);

//FunctionPT
void	display_board(void)
{
	char	buffer[HEIGHT][WIDTH];

	memcpy(buffer, Table, HEIGHT * WIDTH * sizeof(char));
	get_mino_overlay(buffer);
	clear();
	display_title("42 Tetris\n", printw);
	display_array(buffer, printw);
	display_score(g_score, printw);
}

static void	get_mino_overlay(char buffer[HEIGHT][WIDTH])
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
				buffer[current.row+i][current.col+j] += current.array[i][j];
			j++;
		}
		i++;
	}
}
