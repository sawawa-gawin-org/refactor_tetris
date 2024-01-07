#include "tetris.h"

t_shape	FunctionCS(t_shape shape)
{
	t_shape	new_shape = shape;
	char	**copyshape = shape.array;
	int		i;
	int		j;

	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
	for(i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
	}
	return new_shape;
}

void	FunctionDS(t_shape shape)
{
	int i;
	for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
	}
	free(shape.array);
}

int	FunctionCP(t_shape shape)
{
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= C || shape.row+i >= R)){
				if(array[i][j])
					return (0);
			}
			else if(Table[shape.row+i][shape.col+j] && array[i][j])
				return (0);
		}
	}
	return (1);
}

void	FunctionRS(t_shape shape)
{
	t_shape	temp = FunctionCS(shape);
	int 	i;
	int		j;
	int		k;
	int		width;

	width = shape.width;
	i = 0;
	while (i < width)
	{
		j = 0;
		k = width - 1;
		while (j < width)
		{
			shape.array[i][j] = temp.array[k][i];
			j++;
			k--;
		}
		i++;
	}
	FunctionDS(temp);
}

void	FunctionPT(void)
{
	char	Buffer[R][C] = {0};
	int		i;
	int		j;

	i = 0;
	while (i < current.width)
	{
		j = 0;
		while (j < current.width)
		{
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] = current.array[i][j];
			j++;
		}
		i++;
	}
	clear();
	i = 0;
	while (i < C - 9)
	{
		printw(" ");
		i++;
	}
	printw("42 Tetris\n");
	i = 0;
	while (i < R)
	{
		j = 0;
		while (j < C)
		{
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
			j++;
		}
		printw("\n");
		i++;
	}
	printw("\nScore: %d\n", final);
}

int	hasToUpdate(void)
{
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}
