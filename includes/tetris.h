#ifndef TETRIS_H
# define TETRIS_H
# define HEIGHT 20
# define WIDTH 15
# define INITIAL_TIMELIMIT 400000
# define INITIAL_TIMELIMIT_DECREASE 893 // 1/2*893*(893+1) < 400000
# define T 1
# define F 0

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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

extern char				Table[HEIGHT][WIDTH];
extern t_shape			current;

extern int				g_score;
extern suseconds_t		g_timelimit;
extern int				g_decrease;

extern int				GameOn;
extern const t_shape	StructsArray[7];

t_shape		allocate_block(t_shape shape);
t_shape		create_random_block(void);
void		destroy_block(t_shape shape);
int			is_reaching_top(t_shape shape);
void		rotate_block(t_shape shape);
void		display_screen(void);
void		fall_down_block(void);

void		display_board(char array[HEIGHT][WIDTH], int (*print_callback)(const char *fmt, ...));
void		display_title(char *title, int (*print_callback)(const char *fmt, ...));
suseconds_t	gettime_as_us(void);

#endif