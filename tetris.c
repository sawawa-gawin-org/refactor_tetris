#include "tetris.h"

char Table[R][C] = {0};
int final = 0;
char GameOn = T;
suseconds_t timer = 400000;
int decrease = 1000;

t_shape current;

const t_shape StructsArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};

t_shape FunctionCS(t_shape shape){
	t_shape new_shape = shape;
	char **copyshape = shape.array;
	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
    int i, j;
    for(i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}

void FunctionDS(t_shape shape){
    int i;
    for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
    }
    free(shape.array);
}

int FunctionCP(t_shape shape){
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= C || shape.row+i >= R)){
				if(array[i][j])
					return F;
				
			}
			else if(Table[shape.row+i][shape.col+j] && array[i][j])
				return F;
		}
	}
	return T;
}

void FunctionRS(t_shape shape){
	t_shape temp = FunctionCS(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	FunctionDS(temp);
}

void FunctionPT(){
	char Buffer[R][C] = {0};
	int i, j;
	for(i = 0; i < current.width ;i++){
		for(j = 0; j < current.width ; j++){
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] = current.array[i][j];
		}
	}
	clear();
	for(i=0; i<C-9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}

struct timeval before_now, now;
int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}

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
int main()
{
	int	score;

	score = 0;
    final = score;
    // srand(time(0));  // 乱数のseed設定、srand(1)としたら、毎回同じ順序位置でミノが落ちる
	srand(0); // as Debug
    initscr(); // スクリーンを初期化する
	set_timeout(1);  // 現状意図不明
	/* 初期ミノ設定 */
    FunctionDS(current); // グローバル変数なので、前回のミノの明示的解放
	t_shape new_shape = FunctionCS(StructsArray[rand()%7]); // ミノ全7パターンから選択
    new_shape.col = rand() % (C - new_shape.width+1); // 落ちる場所: C:15(グリッド横)
    new_shape.row = 0; // 落ちる場所：[0, R] R:20(グリッド縦)
	current = new_shape;
	/* ゲーム画面高さが1の時なのためにループに入る前に高さ判定を行っているが、
	FunctionPT();が呼び出された際に自動失敗する。
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
			t_shape temp = FunctionCS(current);
			switch(c){
				case 's':
					temp.row++; //move down
					if(FunctionCP(temp))
						current.row++;
					else {

/* 自由落下処理　ここから */
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
/* ここまで */

					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCP(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCP(temp))
						current.col--;
					break;
				case 'w':
					FunctionRS(temp); // 重複している？
					if(FunctionCP(temp))
						FunctionRS(current);
					break;
			}
			FunctionDS(temp);
			FunctionPT();
		}
		gettimeofday(&now, NULL); // 時間経過判定のための時刻取得
		if (hasToUpdate()) { // 時間経過による落下(前回のループ終了からここまでの経過時間が>1sならば)
			t_shape temp = FunctionCS(current);
			temp.row++;
			if(FunctionCP(temp))
				current.row++;
			else {

/* 自由落下処理　ここから */
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
/* ここまで(上記の処理とまったく一緒) */

			}
			FunctionDS(temp);
			FunctionPT();
			gettimeofday(&before_now, NULL);// 時間経過判定のための時刻取得
		}
	}
	FunctionDS(current);
	endwin();
	/* 以降 標準出力での出力 */
	int i, j;
	for(i = 0; i < R ;i++){ // 画面が更新される都合上のループ外での再描画
		for(j = 0; j < C ; j++){
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
    return 0;
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
	t_shape new_shape = FunctionCS(StructsArray[rand()%7]);
	new_shape.col = rand()%(C-new_shape.width+1);
	new_shape.row = 0;
	FunctionDS(current);
	current = new_shape;
	if(!FunctionCP(current)){
		GameOn = F;
	}
}