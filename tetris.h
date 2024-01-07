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

enum	e_interface
{
	ROTATE_KEY = 'w',
	MV_LEFT_KEY = 'a',
	MV_DOWN_KEY = 's',
	MV_RIGHT_KEY = 'd',
};

extern t_shape current;
extern char Table[R][C];
extern int final;
extern suseconds_t timer;
extern struct timeval before_now;
extern struct timeval now;
extern char GameOn;
extern int decrease;
extern const t_shape StructsArray[7];

t_shape	create_new_block(t_shape shape);
void	destroy_old_block(t_shape shape);
int		detect_reaching_top(t_shape shape);
void	rotate_block(t_shape shape);
void	display_board(void);
void 	fall_down_block(void);
int		hasToUpdate(void);

#endif