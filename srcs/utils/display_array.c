#include "tetris.h"

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
