#ifndef TETRIS_H
# define TETRIS_H
# define HEIGHT 20
# define WIDTH 15
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

extern t_shape current;
extern char Table[HEIGHT][WIDTH];
extern int final;
extern suseconds_t timer;
extern struct timeval pre_time;
extern struct timeval now_time;
extern char GameOn;
extern int decrease;
extern const t_shape StructsArray[7];

t_shape	create_new_block(t_shape shape);
t_shape	create_next_block(void);
void	destroy_old_block(t_shape shape);
int		detect_reaching_top(t_shape shape);
void	rotate_block(t_shape shape);
void	display_board(void);
void 	fall_down_block(void);
int		has_to_update(suseconds_t timer);

void	display_array(char array[HEIGHT][WIDTH], int (*print_callback)(const char *fmt, ...));
void	display_title(char *title, int (*print_callback)(const char *fmt, ...));
void	display_score(int score, int (*print_callback)(const char *fmt, ...));

#endif