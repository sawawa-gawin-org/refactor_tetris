#include "tetris.h"

static void	erase_completed_line(int height, int sum);

//行が揃った時、消去して1段下げ、スコアを加算する関数
void put_block_bottom(void)
{
	int height, sum;

	update_table();
	height = 0;
	while (height < HEIGHT)
	{
		sum = sum_array((char *) Table[height], WIDTH);
		if (sum == WIDTH)
		{
			erase_completed_line(height, sum);
		}
		height++;
	}
}

void	update_table(void)
{
	int i, j;

	i = 0;
	while (i < current.size)
	{
		j = 0;
		while (j < current.size)
		{
			if(current.array[i][j])
			{
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

	g_score += 100;
	while (height > 0)
	{
		width = 0;
		while (width < WIDTH)
		{
			Table[height][width] = Table[height - 1][width];
			width++;
		}
		height--;
	}
	width = 0;
	while (width < WIDTH)
	{
		Table[height][width] = 0;
		width++;
	}
	g_decrease = g_decrease > 0 ? g_decrease - 1 : 0; 
	g_timelimit -= g_decrease;
}
