#include "tetris.h"

static void	erase_completed_line(int height, int sum);

//行が揃った時、消去して1段下げ、スコアを加算する関数
//currentはt_shape new=shape
//widthは、正方形の1辺の長さ。取りうる面積。2x2ならwidth2で2x2、1x4はwidth4で4x4の範囲
void put_block_bottom(void)
{
	int height, sum;

	update_table();
	height = 0;
	while (height < HEIGHT)//0-19(ゲーム画面縦)
	{
		//sum：高さnの行にあるブロックの合計数
		sum = sum_array((char *) Table[height], WIDTH);
		if (sum == WIDTH) {// 合計数がゲーム画面横幅に等しいなら
			erase_completed_line(height, sum);
		}
		height++;
	}
}

void	update_table(void)
{
	int i, j;

	i = 0;
	while (i < current.width)//0-ブロックの横幅。正方形の縦
	{
		j = 0;
		while (j < current.width)//0-ブロックの横幅。正方形の横。
		{
			if(current.array[i][j])//もし正方形内のi,jにブロックがあるなら
			{
				//Table(ゲーム盤面)にブロックを置く。
				Table[current.row + i][current.col + j] = current.array[i][j];
			}
			j++;
		}
		i++;
	}
}

static void	erase_completed_line(int height, int sum)
{
	int	width;

	g_score += 100;//スコアを100加算
	while (height > 0)//最上部を除いた高さの間
	{
		width = 0;
		while (width < WIDTH)//横幅の間
		{
			Table[height][width] = Table[height - 1][width];//ブロックを1行ずつ下にずらす。
			width++;
		}
		height--;
	}
	width = 0;
	while (width < WIDTH)
	{
		Table[height][width] = 0;//最上部を0クリア
		width++;
	}
	g_decrease = g_decrease > 0 ? g_decrease - 1 : 0; 
	g_timelimit -= g_decrease;
}
