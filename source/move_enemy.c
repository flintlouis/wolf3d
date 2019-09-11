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
	int i;
	double x;
	double y;

	i = 0;
	while (i < LEVEL->enemy_count)
	{
		if (!ENEMIES[i].ss->hit) {
			ENEMIES[i].start = &mlx->grid[(int)(PLAYER->pos.x - 1)][(int)(PLAYER->pos.y - 1)];
			ENEMIES[i].end = &mlx->grid[(int)(ENEMIES[i].ss->location.x - 1)][(int)(ENEMIES[i].ss->location.y - 1)];
			ENEMIES[i].open_set = ENEMIES[i].start;
			while (ENEMIES[i].open_set && !compare_nodes(ENEMIES[i].path, ENEMIES[i].end))
				find_path(&ENEMIES[i].open_set, &ENEMIES[i].closed_set, &ENEMIES[i].path, ENEMIES[i].end);
			x = ENEMIES[i].ss->location.x + (((ENEMIES[i].path->prev->loc.x + 1.5) - ENEMIES[i].ss->location.x) / 10);
			y = ENEMIES[i].ss->location.y + (((ENEMIES[i].path->prev->loc.y + 1.5) - ENEMIES[i].ss->location.y) / 10);
			if (ENEMIES[i].path->prev->loc.x != ENEMIES[i].start->loc.x || ENEMIES[i].path->prev->loc.y != ENEMIES[i].start->loc.y)
				ENEMIES[i].ss->location = (t_dpoint){x, y};
				// ENEMIES[i].ss->location = (t_dpoint){(ENEMIES[i].path->prev->loc.x + 1.5), (ENEMIES[i].path->prev->loc.y + 1.5)};
			else
				ft_putendl("DEAD");
			free_grid(mlx->grid, (t_point){(LEVEL->size.x - 2), (LEVEL->size.y - 2)});
			ENEMIES[i].start = NULL;
			ENEMIES[i].end = NULL;
			ENEMIES[i].open_set = NULL;
			ENEMIES[i].closed_set = NULL;
			ENEMIES[i].path = NULL;
		}
		i++;
	}
}