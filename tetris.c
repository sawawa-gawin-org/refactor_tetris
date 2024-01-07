#include "tetris.h"

//extern済み
char Table[R][C] = {0};
t_shape current;
int final = 0;
suseconds_t timer = 400000;
struct timeval before_now;
struct timeval now;

//まだ
char GameOn = T;
int decrease = 1000;

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
// FunctionCP: 上まで積み上がったか判定
/* 
# define T 1 : Trueのこと
# define F 0 : Falseのこと
というか、このdefineは<ncurses.h>内部にTRUE/FALSEで存在する。
*/
// t_shapeは{(3,3),(4,1),(2,2)}のグリッド。
// ex: {(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3}
// 最後の要素はブロックの高さサイズ(Iミノは4, Oミノは2)

void FunctionFF(void); //関数名は他の関数の命名規則に合わせるため一時的なもの

static void	display_array(char array[R][C], int (*callback)(const char *fmt, ...));
static void	init_globals(void);

// 不要かもしれない
static void	init_globals(void)
{
	final = 0;
	/* 初期ミノ設定 */
    FunctionDS(current); // グローバル変数なので、前回のミノの明示的解放?
}

int main()
{
	t_shape	new_shape, tmp_shape;

	init_globals();
    // srand(time(0));  // 乱数のseed設定、srand(1)としたら、毎回同じ順序位置でミノが落ちる
	srand(0); // as Debug
    initscr(); // スクリーンを初期化する
	/* TUIの開始 */
	timeout(1);

	/* 以下値の受け渡し方法に改善の余地がある気がする */
	new_shape = FunctionCS(StructsArray[rand()%7]); // ミノ全7パターンから選択
    new_shape.col = rand() % (C - new_shape.width+1); // 落ちる場所: C:15(グリッド横)
    new_shape.row = 0; // 落ちる場所：[0, R] R:20(グリッド縦)
	current = new_shape;

	/* ゲーム画面高さが1の時なのためにループに入る前に高さ判定を行っている、
	現状のバグでFunctionPT();が呼び出された際に自動失敗
	 */
	if(!FunctionCP(current)){
		GameOn = F;
	}
	gettimeofday(&before_now, NULL); //時刻の取得(datetime.now()と同じ) 画面更新間隔の計算で使用
    FunctionPT();
	/* 2 パターンの処理がゲーム終了まで続く半無限ループ 
		// 1. キーボードのwasdの有無の確認とそれに応じた処理
		// 2. 猶予内までに入力が無ければ自由落下
	*/
    int	c;
	while(GameOn){
		if ((c = getch()) != ERR) {
			tmp_shape = FunctionCS(current);
			if (c == MV_DOWN_KEY)
			{
				tmp_shape.row++;
				if (FunctionCP(tmp_shape))
					current.row++;
				else
					FunctionFF();
			}
			else if (c == MV_RIGHT_KEY)
			{
				tmp_shape.col++;
				if (FunctionCP(tmp_shape))
					current.col++;
			}
			else if (c == MV_LEFT_KEY)
			{
				tmp_shape.col--;
				if(FunctionCP(tmp_shape))
					current.col--;
			}
			else if (c == ROTATE_KEY)
			{
				FunctionRS(tmp_shape);
				if (FunctionCP(tmp_shape))
					FunctionRS(current);
			}
			FunctionDS(tmp_shape);
			FunctionPT();
		}
		gettimeofday(&now, NULL); // 時間経過判定のための時刻取得
		if (hasToUpdate()) { // 時間経過による落下(前回のループ終了からここまでの経過時間が>1sならば)
			tmp_shape = FunctionCS(current);
			tmp_shape.row++;
			if(FunctionCP(tmp_shape))
				current.row++;
			else {
				FunctionFF();
			}
			FunctionDS(tmp_shape);
			FunctionPT();
			gettimeofday(&before_now, NULL);// 時間経過判定のための時刻取得
		}
	}
	FunctionDS(current);
	endwin();
	/* 以降 標準出力での出力 */
	int	score;

	score = final;
	display_array(Table, printf);
	printf("\nGame over!\n");
	printf("\nScore: %d\n", score);
    return 0;
}

static void	display_array(char array[R][C], int (*callback)(const char *fmt, ...))
{
	int i, j;
	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			callback("%c ", array[i][j] ? '#': '.');
		}
		callback("\n");
	}
}

void FunctionFF(void)
{
	int i, j;
	for(i = 0; i < current.width ;i++){
		for(j = 0; j < current.width ; j++){
			if(current.array[i][j])
				Table[current.row+i][current.col+j] = current.array[i][j];
		}
	}
	int n, m, sum, count=0;
	for(n=0;n<R;n++){
		sum = 0;
		for(m=0;m< C;m++) {
			sum+=Table[n][m];
		}
		if(sum==C){
			count++;
			int l, k;
			for(k = n;k >=1;k--)
				for(l=0;l<C;l++)
					Table[k][l]=Table[k-1][l];
			for(l=0;l<C;l++)
				Table[k][l]=0;
			timer-=decrease--;
		}
	}
	final += 100*count;
	t_shape new_shape = FunctionCS(StructsArray[rand()%7]);
	new_shape.col = rand()%(C-new_shape.width+1);
	new_shape.row = 0;
	FunctionDS(current);
	current = new_shape;
	if(!FunctionCP(current)){
		GameOn = F;
	}
}
