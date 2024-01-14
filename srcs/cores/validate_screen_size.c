#include "tetris.h"

static int	get_mino_max_size(const t_shape *tetriminos, int kinds_minos);

int	validate_screen_size(const t_shape *tetriminos, int kinds_minos)
{
	int		max_size;

	if (tetriminos == NULL)
		return (0);
	max_size = get_mino_max_size((t_shape *) tetriminos, kinds_minos);
	if (max_size > WIDTH || max_size > HEIGHT)
	{
		fprintf(stderr, "%s\n", "Error: tetriminos are too big to fit in the game grid size\n");
		return (ERR);
	}
	return (OK);
}

static int	get_mino_max_size(const t_shape *tetriminos, int kinds_minos)
{
	int	i;
	int	max_size;
	t_shape mino;

	if (tetriminos == NULL)
		return (0);
	i = 0;
	max_size = 0;
	while (i < kinds_minos)
	{
		mino = tetriminos[i];
		max_size = (max_size < mino.width) ? mino.width : max_size;
		i++;
	}
	return (max_size);
}
