#include "tetris.h"

static void	get_block_overlay(char buffer[HEIGHT][WIDTH]);

//ゲーム画面全体(タイトル、ボード、スコア)を描画する関数
void	display_game(void)
{
	char	buffer[HEIGHT][WIDTH];

	memcpy(buffer, g_table, HEIGHT * WIDTH * sizeof(char));
	get_block_overlay(buffer);
	clear();
	display_title("42 Tetris\n", printw);
	display_board(buffer, printw);
	printw("\nScore: %d\n", g_score);
}

static void	get_block_overlay(char buffer[HEIGHT][WIDTH])
{
	int		i, j;

	i = 0;
	while (i < g_current.size)
	{
		j = 0;
		while (j < g_current.size)
		{
			if(g_current.array[i][j])
				buffer[g_current.row + i][g_current.col + j] += g_current.array[i][j];
			j++;
		}
		i++;
	}
}
