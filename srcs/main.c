#include "tetris.h"

char			Table[HEIGHT][WIDTH] = {0};
t_shape			current;

int				g_score = 0;
suseconds_t		g_timelimit = INITIAL_TIMELIMIT;
int				g_decrease = INITIAL_TIMELIMIT_DECREASE;

int				GameOn = FALSE;

// このミノの構造体は上に揃えないといけない
const t_shape StructsArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3}, // S mino
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3}, // Z mino
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3}, // T mino
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3}, // L mino
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3}, // J mino
	{(char *[]){(char []){1,1},(char []){1,1}}, 2}, // O mino
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4} // I mino
};

static void	update_with_key_press(int input_key);
static void	update_with_limit();

int	main(void)
{
	suseconds_t	pre_time, now_time;
	int			input_key;

	destroy_block(current);
    srand(time(0));

	/* TUIの開始 */
    initscr();
	timeout(1);
	current = create_random_block();
	/* ゲーム画面高さが1の時なのためにループに入る前に高さ判定を行っている、 */
	if(!is_reaching_bottom(current)){ //create_next_blockを呼ぶ部分は共通してこの処理をやっているので、共通にしてもいいかも
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

	tmp_shape = allocate_block(current);
	if (input_key == MV_DOWN_KEY)
	{
		tmp_shape.row++;
		if (!is_reaching_bottom(tmp_shape))
			current.row++;
		else {
			fall_down_block();
			destroy_block(current);
			current = create_random_block();
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
		rotate_block(tmp_shape);//tmp_shapeが90度右に回転する。
		if (!is_reaching_bottom(tmp_shape))
			rotate_block(current);//currentが90度右に回転する。
	}
	destroy_block(tmp_shape);
	display_screen();
}

static void	update_with_limit()
{
	t_shape	tmp_shape;

	tmp_shape = allocate_block(current);
	tmp_shape.row++;
	if(!is_reaching_bottom(tmp_shape))
		current.row++;
	else {
		fall_down_block();
		destroy_block(current);
		current = create_random_block();
		if(is_reaching_bottom(current)){
			GameOn = FALSE;
		}
	}
	destroy_block(tmp_shape);
	display_screen();
}
