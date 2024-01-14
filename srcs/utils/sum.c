int	sum_array(char *array, int size)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < size)
	{
		sum += (int) array[i];
		i++;
	}
	return (sum);
}
