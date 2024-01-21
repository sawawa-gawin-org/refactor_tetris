#include "tetris.h"

char			Table[HEIGHT][WIDTH] = {};
t_shape			current;

int				g_score = 0;
suseconds_t		g_timelimit = INITIAL_TIMELIMIT;
int				g_decrease = INITIAL_TIMELIMIT_DECREASE;

int				GameOn = FALSE;

static const t_shape tetriminos[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3, 0, 0}, // S mino
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3, 0, 0}, // Z mino
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0}, // T mino
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0}, // L mino
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0}, // J mino
	{(char *[]){(char []){1,1},(char []){1,1}}, 2, 0, 0}, // O mino
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4, 0, 0} // I mino
};

static void	update_with_key_press(int input_key);
static void	update_with_limit();

int	main(void)
{
	suseconds_t	pre_time, now_time;
	size_t		kinds_minos;
	int			input_key;

	kinds_minos = sizeof(tetriminos) / sizeof(tetriminos[0]);
	if (validate_screen_size(tetriminos, kinds_minos) == ERR)
		exit(1);
	destroy_block(current);
    srand(time(0));
	/* TUIの開始 */
    initscr();
	timeout(1);
	current = create_random_block(tetriminos);
	/* ゲーム画面高さが1の時なのためにループに入る前に高さ判定を行っている、 */
	if(!is_reaching_bottom(current))
	{
		GameOn = TRUE;
		display_screen();
	}
	pre_time = gettime_as_us();
	while(GameOn)
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
	destroy_block(current);
	endwin();
	/* TUIの終了 */
	display_board(Table, printf);
	printf("\nGame over!\n\nScore: %d\n", g_score);
	return (0);
}

static void	update_with_key_press(int input_key)
{
	t_shape	tmp_shape;

	tmp_shape = duplicate_block(current);
	if (input_key == MV_DOWN_KEY)
	{
		tmp_shape.row++;
		if (!is_reaching_bottom(tmp_shape))
			current.row++;
		else {
			put_block_bottom();
			destroy_block(current);
			current = create_random_block(tetriminos);
			if(is_reaching_bottom(current))
				GameOn = FALSE;
		}
	}
	else if (input_key == MV_RIGHT_KEY)
	{
		tmp_shape.col++;
		if (!is_reaching_bottom(tmp_shape))
			current.col++;
	}
	else if (input_key == MV_LEFT_KEY)
	{
		tmp_shape.col--;
		if(!is_reaching_bottom(tmp_shape))
			current.col--;
	}
	else if (input_key == ROTATE_KEY)
	{
		rotate_block(tmp_shape);
		if (!is_reaching_bottom(tmp_shape))
			rotate_block(current);
	}
	destroy_block(tmp_shape);
	display_screen();
}

static void	update_with_limit()
{
	t_shape	tmp_shape;

	tmp_shape = duplicate_block(current);
	tmp_shape.row++;
	if(!is_reaching_bottom(tmp_shape))
		current.row++;
	else {
		put_block_bottom();
		destroy_block(current);
		current = create_random_block(tetriminos);
		if(is_reaching_bottom(current)){
			GameOn = FALSE;
		}
	}
	destroy_block(tmp_shape);
	display_screen();
}
