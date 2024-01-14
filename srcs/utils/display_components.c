#include "tetris.h"

void	display_board(char array[HEIGHT][WIDTH], int (*print_callback)(const char *fmt, ...))
{
	int i, j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			print_callback("%c ", array[i][j] ? '#': '.');
			j++;
		}
		print_callback("\n");
		i++;
	}
}

void	display_title(char *title, int (*print_callback)(const char *fmt, ...))
{
	int	i;

	i = 0;
	while (i < WIDTH - 9) // why 9? wakaranai...
	{
		print_callback(" ");
		i++;
	}
	print_callback("42 Tetris\n");
}
