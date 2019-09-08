#include "wolf3d.h"

void find_path(t_node **openSet, t_node **closedSet, t_node **path, t_node *end);
int compare_nodes(t_node *s1, t_node *s2);

static void free_grid(t_node **grid, t_point grid_size)
{
	int i;
	int j;

	i = 0;
	while (i < grid_size.x)
	{
		j = 0;
		while (j < grid_size.y)
		{
			grid[i][j].next = NULL;
			grid[i][j].prev = NULL;
			grid[i][j].f = 0;
			grid[i][j].g = 0;
			grid[i][j].h = 0;
			j++;
		}
		i++;
	}
}

void move_enemy(t_mlx *mlx)
{
	if (ENEMIES[0].ss->hit)
		return ;
	ENEMIES[0].start = &mlx->grid[(int)(PLAYER->pos.x - 1)][(int)(PLAYER->pos.y - 1)];
	ENEMIES[0].end = &mlx->grid[(int)(ENEMIES[0].ss->location.x - 1)][(int)(ENEMIES[0].ss->location.y - 1)];
	ENEMIES[0].open_set = ENEMIES[0].start;
	while (ENEMIES[0].open_set && !compare_nodes(ENEMIES[0].path, ENEMIES[0].end))
		find_path(&ENEMIES[0].open_set, &ENEMIES[0].closed_set, &ENEMIES[0].path, ENEMIES[0].end);
	system("clear");	
		printf("start : (%d, %d), path : (%d, %d)\n\n", ENEMIES[0].start->loc.x + 1, ENEMIES[0].start->loc.y + 1, ENEMIES[0].path->prev->loc.x + 1, ENEMIES[0].path->prev->loc.y + 1);
	if (ENEMIES[0].path->prev->loc.x != ENEMIES[0].start->loc.x || ENEMIES[0].path->prev->loc.y != ENEMIES[0].start->loc.y)
		ENEMIES[0].ss->location = (t_dpoint){(ENEMIES[0].path->prev->loc.x + 1.5), (ENEMIES[0].path->prev->loc.y + 1.5)};
	free_grid(mlx->grid, (t_point){(LEVEL->size.x - 2), (LEVEL->size.y - 2)});
	ENEMIES[0].start = NULL;
	ENEMIES[0].end = NULL;
	ENEMIES[0].open_set = NULL;
	ENEMIES[0].closed_set = NULL;
	ENEMIES[0].path = NULL;
}