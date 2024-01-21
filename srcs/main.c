#include "tetris.h"

char			g_table[HEIGHT][WIDTH] = {};
t_shape			g_current;
int				g_score = 0;
time_t			g_timelimit = INITIAL_TIMELIMIT;
int				g_decrease = INITIAL_TIMELIMIT_DECREASE;

const t_shape tetriminos[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3, 0, 0}, // S mino
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3, 0, 0}, // Z mino
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0}, // T mino
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0}, // L mino
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0}, // J mino
	{(char *[]){(char []){1,1},(char []){1,1}}, 2, 0, 0}, // O mino
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4, 0, 0} // I mino
};

int		game_on = TRUE;

static void	update_with_key_press(int input_key);
static void	update_with_limit();

int	main(void)
{
	size_t		kinds_tetriminos;
	time_t		pre_time, now_time;
	int			input_key;

	kinds_tetriminos = sizeof(tetriminos) / sizeof(tetriminos[0]);
	if (validate_screen_size(tetriminos, kinds_tetriminos) == ERR)
		exit(1);
	destroy_block(g_current);
	srand(time(0));
	initscr();
	timeout(1);
	g_current = create_random_block(tetriminos);
	pre_time = gettime_as_us();
	while(game_on)
	{
		if ((input_key = getch()) != ERR)
		{
			update_with_key_press(input_key);
		}
		now_time = gettime_as_us();
		if (now_time - pre_time > g_timelimit)
		{
			update_with_limit();
			pre_time = gettime_as_us();
		}
	}
	destroy_block(g_current);
	endwin();
	display_board(g_table, printf);
	printf("\nGame over!\n\nScore: %d\n", g_score);
	return (0);
}

static void	update_with_key_press(int input_key)
{
	t_shape	tmp_shape;

	tmp_shape = duplicate_block(g_current);
	if (input_key == MV_DOWN_KEY)
	{
		tmp_shape.row++;
		if (!is_reaching_bottom(tmp_shape))
			g_current.row++;
		else {
			put_block_bottom();
			destroy_block(g_current);
			g_current = create_random_block(tetriminos);
			if(is_reaching_bottom(g_current))
				game_on = FALSE;
		}
	}
	else if (input_key == MV_RIGHT_KEY)
	{
		tmp_shape.col++;
		if (!is_reaching_bottom(tmp_shape))
			g_current.col++;
	}
	else if (input_key == MV_LEFT_KEY)
	{
		tmp_shape.col--;
		if(!is_reaching_bottom(tmp_shape))
			g_current.col--;
	}
	else if (input_key == ROTATE_KEY)
	{
		rotate_block(tmp_shape);
		if (!is_reaching_bottom(tmp_shape))
			rotate_block(g_current);
	}
	destroy_block(tmp_shape);
	display_game();
}

static void	update_with_limit()
{
	t_shape	tmp_shape;

	tmp_shape = duplicate_block(g_current);
	tmp_shape.row++;
	if(!is_reaching_bottom(tmp_shape))
		g_current.row++;
	else {
		put_block_bottom();
		destroy_block(g_current);
		g_current = create_random_block(tetriminos);
		if(is_reaching_bottom(g_current)){
			game_on = FALSE;
		}
	}
	destroy_block(tmp_shape);
	display_game();
}
