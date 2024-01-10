#include "../tetris.h"

char			Table[HEIGHT][WIDTH] = {0};
t_shape			current;

int				g_score = 0;
suseconds_t		g_interval = INITIAL_UPDATE_INTERVAL;
int				g_decrease = INITIAL_INTERVAL_DECREASE;
struct timeval	g_pre_time;
struct timeval	g_now_time;

char			GameOn = TRUE;

const t_shape StructsArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};

static void	update_with_key_press(int input_key);
static void	update_with_limit();

// create_new_block: 落下してくるブロックの配列にメタデータを付与して返す。
// destroy_old_block: 配列のオブジェクトを解放する。
// rotate_block: 配列のオブジェクトを回転？
// display_screen: 背景オブジェクト、タイトルとかスコアの表示
// detect_reaching_top: 上まで積み上がったか判定

// t_shapeは{(3,3),(4,1),(2,2)}のグリッド。
// ex: {(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3}
// 最後の要素はブロックの高さサイズ(Iミノは4, Oミノは2)

int	main(void)
{
	int	input_key;

	destroy_old_block(current);
    // srand(time(0));
	srand(0); // as Debug

	/* TUIの開始 */
    initscr(); // スクリーンを初期化する
	timeout(1);
	current = create_next_block();//fall_down_blocksに同様の箇所があったため共通化しました
	/* ゲーム画面高さが1の時なのためにループに入る前に高さ判定を行っている、
	現状のバグでFunctionPT();が呼び出された際に自動失敗
	 */
	if(detect_reaching_top(current))//create_next_blockを呼ぶ部分は共通してこの処理をやっているので、共通にしてもいいかも
		GameOn = FALSE;

	gettimeofday(&g_pre_time, NULL); //時刻の取得(datetime.g_now_time()と同じ) 画面更新間隔の計算で使用
	display_screen();
	while(GameOn)
	{
		if ((input_key = getch()) != ERR)
		{
			update_with_limit(input_key);
		}
		gettimeofday(&g_now_time, NULL); // 時間経過判定のための時刻取得
		if (has_to_update(g_interval))
		{
			update_with_key_press();
			gettimeofday(&g_pre_time, NULL);// 時間経過判定のための時刻取得
		}
	}
	destroy_old_block(current);
	endwin();
	/* 以降 標準出力での出力 */
	display_board(Table, printf);
	printf("\nGame over!\n\nScore: %d\n", g_score);
	return (0);
}

static void	update_with_key_press(int input_key)
{
	t_shape	tmp_shape;

	tmp_shape = create_new_block(current);
	if (input_key == MV_DOWN_KEY)
	{
		tmp_shape.row++;
		if (!detect_reaching_top(tmp_shape))
			current.row++;
		else
			fall_down_blocks();
	}
	else if (input_key == MV_RIGHT_KEY)
	{
		tmp_shape.col++;
		if (!detect_reaching_top(tmp_shape))
			current.col++;
	}
	else if (input_key == MV_LEFT_KEY)
	{
		tmp_shape.col--;
		if(!detect_reaching_top(tmp_shape))
			current.col--;
	}
	else if (input_key == ROTATE_KEY)
	{
		rotate_block(tmp_shape);//tmp_shapeが90度右に回転する。
		if (!detect_reaching_top(tmp_shape))
			rotate_block(current);//currentが90度右に回転する。
	}
	destroy_old_block(tmp_shape);
	display_screen();
}

static void	update_with_limit()
{
	t_shape	tmp_shape;

	tmp_shape = create_new_block(current);
	tmp_shape.row++;
	if(!detect_reaching_top(tmp_shape))
		current.row++;
	else
		fall_down_blocks();
	destroy_old_block(tmp_shape);
	display_screen();
}
