#ifndef TETRIS_H
# define TETRIS_H
# define HEIGHT 20
# define WIDTH 15
# define INITIAL_TIMELIMIT 400000
# define INITIAL_TIMELIMIT_DECREASE 893 // 1/2*893*(893+1) < 400000
# define SCORE_INCREMENT_RATE 100

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <ncurses.h>

typedef struct s_shape
{
	char	**array;
	int		size;
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

extern char				g_table[HEIGHT][WIDTH];
extern t_shape			g_current;

extern int				g_score;
extern time_t			g_timelimit;
extern int				g_decrease;

t_shape		duplicate_block(t_shape shape);
t_shape		create_random_block(const t_shape *tetriminos);
void		destroy_block(t_shape shape);
int			is_reaching_bottom(t_shape shape);
void		rotate_block(t_shape shape);
void		display_game(void);
void		put_block_bottom(void);
int			validate_screen_size(const t_shape *tetriminos, int kinds_minos);

void		display_board(char array[HEIGHT][WIDTH], int (*print_callback)(const char *fmt, ...));
void		display_title(char *title, int (*print_callback)(const char *fmt, ...));
time_t		gettime_as_us(void);
int			sum_array(char *array, int size);

#endif