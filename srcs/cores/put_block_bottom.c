#include "tetris.h"

static void	update_table(void);
static void	erase_completed_line(int height);

//行が揃った時、消去して1段下げ、スコアを加算する関数
void put_block_bottom(void)
{
	int height, sum;

	update_table();
	height = 0;
	while (height < HEIGHT)
	{
		sum = sum_array((char *) g_table[height], WIDTH);
		if (sum == WIDTH)
		{
			erase_completed_line(height);
		}
		height++;
	}
}

static void	update_table(void)
{
	int i, j;

	i = 0;
	while (i < g_current.size)
	{
		j = 0;
		while (j < g_current.size)
		{
			if(g_current.array[i][j])
			{
				g_table[g_current.row + i][g_current.col + j] = g_current.array[i][j];
			}
			j++;
		}
		i++;
	}
}

static void	erase_completed_line(int height)
{
	int	width;

	g_score += 100;
	while (height > 0)
	{
		width = 0;
		while (width < WIDTH)
		{
			g_table[height][width] = g_table[height - 1][width];
			width++;
		}
		height--;
	}
	width = 0;
	while (width < WIDTH)
	{
		g_table[height][width] = 0;
		width++;
	}
	g_decrease = g_decrease > 0 ? g_decrease - 1 : 0; 
	g_timelimit -= g_decrease;
}
