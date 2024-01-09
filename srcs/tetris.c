#include "../tetris.h"

char			Table[HEIGHT][WIDTH] = {0};
t_shape			current;

int				g_score;
suseconds_t		g_interval;
int				g_decrease; // 画面更新間隔の減少量
struct timeval	g_pre_time;
struct timeval	g_now_time;

char			GameOn = T;

const t_shape StructsArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};

// FunctionCS: 落下してくるブロックの配列にメタデータを付与して返す。
// FunctionDS: 配列のオブジェクトを解放する。
// FunctionRS: 配列のオブジェクトを回転？
// FunctionPT: 背景オブジェクト、タイトルとかスコアの表示
// detect_reaching_top: 上まで積み上がったか判定
/* 
# define T 1 : Trueのこと
# define F 0 : Falseのこと
というか、このdefineは<ncurses.h>内部にTRUE/FALSEで存在する。
*/
// t_shapeは{(3,3),(4,1),(2,2)}のグリッド。
// ex: {(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3}
// 最後の要素はブロックの高さサイズ(Iミノは4, Oミノは2)

static void	init_globals(void);

// 不要かもしれない
static void	init_globals(void)
{
	g_score = 0;
	g_interval = INITIAL_UPDATE_INTERVAL;
	g_decrease = INITIAL_INTERVAL_DECREASE;
	/* 初期ミノ設定 */
    destroy_old_block(current); // グローバル変数なので、前回のミノの明示的解放?
}

int	main(void)
{
	t_shape	new_shape, tmp_shape;

	init_globals();
    // srand(time(0));  // 乱数のseed設定、srand(1)としたら、毎回同じ順序位置でミノが落ちる
	srand(0); // as Debug
    initscr(); // スクリーンを初期化する
	/* TUIの開始 */
	timeout(1);

	/* 以下値の受け渡し方法に改善の余地がある気がする */
	// new_shape = create_new_block(StructsArray[rand()%7]); // ミノ全7パターンから選択
    // new_shape.col = rand() % (WIDTH - new_shape.width+1); // 落ちる場所: WIDTH:15(グリッド横)
    // new_shape.row = 0; // 落ちる場所：[0, HEIGHT] HEIGHT:20(グリッド縦)
	// current = new_shape;
	
	current = create_next_block();//fall_down_autoに同様の箇所があったため共通化しました

	/* ゲーム画面高さが1の時なのためにループに入る前に高さ判定を行っている、
	現状のバグでFunctionPT();が呼び出された際に自動失敗
	 */
	if(!detect_reaching_top(current)){
		GameOn = F;
	}
	gettimeofday(&g_pre_time, NULL); //時刻の取得(datetime.g_now_time()と同じ) 画面更新間隔の計算で使用
	display_board();
	/* 2 パターンの処理がゲーム終了まで続く半無限ループ 
		// 1. キーボードのwasdの有無の確認とそれに応じた処理
		// 2. 猶予内までに入力が無ければ自由落下
	*/
	int	c;
	while(GameOn){
		if ((c = getch()) != ERR) {
			tmp_shape = create_new_block(current);
			if (c == MV_DOWN_KEY)
			{
				tmp_shape.row++;
				if (detect_reaching_top(tmp_shape))
					current.row++;
				else
					fall_down_block();
			}
			else if (c == MV_RIGHT_KEY)
			{
				tmp_shape.col++;
				if (detect_reaching_top(tmp_shape))
					current.col++;
			}
			else if (c == MV_LEFT_KEY)
			{
				tmp_shape.col--;
				if(detect_reaching_top(tmp_shape))
					current.col--;
			}
			else if (c == ROTATE_KEY)
			{
				rotate_block(tmp_shape);
				if (detect_reaching_top(tmp_shape))
					rotate_block(current);
			}
			destroy_old_block(tmp_shape);
			display_board();
		}
		gettimeofday(&g_now_time, NULL); // 時間経過判定のための時刻取得
		if (has_to_update(g_interval)) {
			tmp_shape = create_new_block(current);
			tmp_shape.row++;
			if(detect_reaching_top(tmp_shape))
				current.row++;
			else {
				fall_down_block();
			}
			destroy_old_block(tmp_shape);
			display_board();
			gettimeofday(&g_pre_time, NULL);// 時間経過判定のための時刻取得
		}
	}
	destroy_old_block(current);
	endwin();
	/* 以降 標準出力での出力 */
	display_array(Table, printf);
	printf("\nGame over!\n");
	display_score(g_score, printf);
    return 0;
}
