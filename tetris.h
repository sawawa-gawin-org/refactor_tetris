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

extern t_shape current;
extern char Table[R][C];
extern int final;
extern suseconds_t timer;
extern struct timeval before_now;
extern struct timeval now;


t_shape	FunctionCS(t_shape shape);
void	FunctionDS(t_shape shape);
int		FunctionCP(t_shape shape);
void	FunctionRS(t_shape shape);
void	FunctionPT(void);
int		hasToUpdate(void);

#endif