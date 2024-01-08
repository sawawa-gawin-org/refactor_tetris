#include "../tetris.h"

static void	get_mino_overlay(char Buffer[R][C]);
static void	display_title(char *title, int (*print_callback)(const char *fmt, ...));
static void	display_score(int score, int (*print_callback)(const char *fmt, ...));

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

static void	display_title(char *title, int (*print_callback)(const char *fmt, ...))
{
	int	i;

	i = 0;
	while (i < C - 9)
	{
		print_callback(" ");
		i++;
	}
	print_callback("42 Tetris\n");
}

static void	display_score(int score, int (*print_callback)(const char *fmt, ...))
{
	print_callback("\nScore: %d\n", score);
}
