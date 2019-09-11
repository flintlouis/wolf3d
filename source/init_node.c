#include "wolf3d.h"

static void init_grid(t_mlx *mlx, t_point grid_size)
{
	int i;
	int j;

	i = 0;
	mlx->grid = (t_node**)ft_memalloc(sizeof(t_node*) * grid_size.y);
	while (i < grid_size.y)
	{
		j = 0;
		mlx->grid[i] = (t_node*)ft_memalloc(sizeof(t_node) * grid_size.x);
		while (j < grid_size.x)
		{
			mlx->grid[i][j].loc = (t_point){i,j};
			mlx->grid[i][j].neighbors = (t_node**)ft_memalloc(sizeof(t_node*) * 4);
			if (MAP[(j + 1)][(i + 1)] > 0 && MAP[(j + 1)][(i + 1)] <= OBJECTCOL)
				mlx->grid[i][j].obstacle = 1;
			j++;
		}
		i++;
	}
}

static void add_neighbors(t_node **grid, t_point grid_size)
{
	int i;
	int j;

	i = 0;
	while (i < grid_size.y)
	{
		j = 0;
		while (j < grid_size.x)
		{
			if (i < grid_size.x - 1 && !grid[i + 1][j].obstacle)
				grid[i][j].neighbors[0] = &grid[i + 1][j];
			if (i > 0 && !grid[i - 1][j].obstacle)
				grid[i][j].neighbors[1] = &grid[i - 1][j];
			if (j < grid_size.y - 1 && !grid[i][j + 1].obstacle)
				grid[i][j].neighbors[2] = &grid[i][j + 1];
			if (j > 0 && !grid[i][j - 1].obstacle)
				grid[i][j].neighbors[3] = &grid[i][j - 1];
			j++;
		}
		i++;
	}
}

void init_pathfinding(t_mlx *mlx)
{
	t_point grid_size;

	grid_size = (t_point){(LEVEL->size.x - 2), (LEVEL->size.y - 2)};
	init_grid(mlx, grid_size);
	add_neighbors(mlx->grid, grid_size);
}