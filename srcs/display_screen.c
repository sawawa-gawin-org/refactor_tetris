#include "tetris.h"

static void	get_mino_overlay(char buffer[HEIGHT][WIDTH]);

//ゲーム画面全体(タイトル、ボード、スコア)を描画する関数
void	display_screen(void)
{
	char	buffer[HEIGHT][WIDTH];

	memcpy(buffer, Table, HEIGHT * WIDTH * sizeof(char));
	get_mino_overlay(buffer);
	clear();
	display_title("42 Tetris\n", printw);
	display_board(buffer, printw);
	printw("\nScore: %d\n", g_score);
}

static void	get_mino_overlay(char buffer[HEIGHT][WIDTH])
{
	int		i, j;

	i = 0;
	while (i < current.width)
	{
		j = 0;
		while (j < current.width)
		{
			if(current.array[i][j])
				buffer[current.row + i][current.col + j] += current.array[i][j];
			j++;
		}
		i++;
	}
}
