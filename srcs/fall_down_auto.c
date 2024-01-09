#include "../tetris.h"

void fall_down_block(void)
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
	t_shape new_shape = create_new_block(StructsArray[rand()%7]);
	new_shape.col = rand()%(C-new_shape.width+1);
	new_shape.row = 0;
	destroy_old_block(current);
	current = new_shape;
	if(!detect_reaching_top(current)){
		GameOn = F;
	}
}
