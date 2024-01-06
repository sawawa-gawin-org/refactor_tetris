#ifndef TETRIS_H
# define TETRIS_H
# define R 20
# define C 15
# define T 1
# define F 0

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <ncurses.h>

typedef struct s_shape
{
	char	**array;
	int		width;
	int		row;
	int		col;
}			t_shape;
#endif