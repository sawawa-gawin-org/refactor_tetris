#include "../../tetris.h"

void	display_array(char array[R][C], int (*print_callback)(const char *fmt, ...))
{
	int i, j;

	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			print_callback("%c ", array[i][j] ? '#': '.');
		}
		print_callback("\n");
	}
}

void	display_title(char *title, int (*print_callback)(const char *fmt, ...))
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

void	display_score(int score, int (*print_callback)(const char *fmt, ...))
{
	print_callback("\nScore: %d\n", score);
}
