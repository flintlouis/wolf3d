/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wolf3d.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:53:21 by fhignett       #+#    #+#                */
/*   Updated: 2019/09/25 16:25:58 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "ft_printf.h"
# include <pthread.h>

/*
** WALLCOUNT		AMOUNT OF WALLS
** OBJECTCOL		AMOUNT OF OBJECTS WITH COLLISION
** ENEMY			ENEMY NUMBER ON MAP 
*/

# define MEM(x) 		(x*)ft_memalloc(sizeof(x))
# define WIDTH			1200
# define HEIGHT			800
# define THREAD			4
# define WALLCOUNT		5
# define OBJECTCOL		11
# define ENEMY			14
# define MAP			mlx->level->map
# define LEVEL			mlx->level
# define PLAYER			mlx->player
# define CONTROLS		mlx->controls
# define TEXTURES		mlx->textures
# define OBJECTS		mlx->objects
# define SPRITE			mlx->sprite
# define GUN			mlx->gun
# define ENEMIES		mlx->enemies

# define KEY_ESC                53
# define KEY_SPACE              49
# define KEY_LSHIFT             257
# define KEY_RSHIFT             258
# define KEY_UP                 126
# define KEY_DOWN               125
# define KEY_RIGHT              124
# define KEY_LEFT               123
# define KEY_W                  13
# define KEY_A                  0
# define KEY_S                  1
# define KEY_D                  2
# define KEY_PLUS               24
# define KEY_MIN                27
# define KEY_R                  15
# define KEY_G                  5
# define KEY_I                  34
# define KEY_ENTER              36
# define L_MOUSE                1
# define R_MOUSE                2
# define WHEEL_FORW             4
# define WHEEL_BACK             5
# define KEY_1                  18
# define KEY_2                  19
# define KEY_3                  20
# define KEY_P                  35

typedef unsigned char	t_byte;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_dpoint
{
	double				x;
	double				y;
}						t_dpoint;

typedef struct			s_colour
{
	t_byte				r;
	t_byte				g;
	t_byte				b;
	t_byte				opacity;
}						t_colour;

typedef struct			s_raycaster
{
	t_point				step;
	t_point				map_pos;
	t_dpoint			side_dist;
	t_dpoint			delta_dist;
	t_dpoint			dir;
}						t_raycaster;

typedef struct			s_draw
{
	int					height;
	int					start;
	int					end;
	int					x;
	int					side;
}						t_draw;

typedef struct			s_texture
{
	int					width;
	int					height;
	t_colour			**colours;
}						t_texture;

typedef	struct 			s_mapobject
{
	int					id;
	int					hit;
	long				ms;
	t_dpoint			rel_loc;
	t_dpoint			location;
	t_texture			sprite;
}						t_mapobject;

typedef struct			s_player
{
	int					health;
	t_dpoint			pos;
	t_dpoint			looking_dir;
	t_dpoint			plane;
	double				angle;
}						t_player;

typedef struct			s_controls
{
	char				shoot:1;
	char				run:1;
	char				front:1;
	char				back:1;
	char				left:1;
	char				right:1;
	char				look_left:1;
	char				look_right:1;
}						t_controls;

typedef struct			s_level
{
	int					object_count;
	int					enemy_count;
	int					**map;
	t_point				size;
}						t_level;

typedef struct			s_prite
{
	int					start;
	int					end;
	int					height;
	int					draw_start;
	int					draw_end;
	int					id;
}						t_sprite;

/*
** f(n) = g(n) + h(n)
** g = steps taken from start
** h = estimated distance to end
*/

typedef struct			s_node
{
	double				f;
	double				g;
	double				h;
	char				obstacle:1;
	t_point				loc;
	struct s_node		**neighbors;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct			s_enemy
{
	int					shoot;
	t_node				*open_set;
	t_node				*closed_set;
	t_node				*path;
	t_node				*start;
	t_node				*end;
	t_mapobject			*ss;
}						t_enemy;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	int					x[2];
	double				*z;
	t_level				*level;
	t_player			*player;
	t_controls			*controls;
	t_texture			*textures;
	t_texture			*gun;
	t_sprite			*sprite;
	t_mapobject			*objects;
	t_enemy				*enemies;
	t_node				**grid;
}						t_mlx;

int						compare_mapobject_distance(const void *a, const void *b);
int						compare_nodes(t_node *s1, t_node *s2);
int						close_window(void *ptr);
int						frames(void);
int						key_press(int key, t_mlx *mlx);
int						key_release(int key, t_mlx *mlx);
int						mouse_move(int x, int y, t_mlx *mlx);
int						wall_hit(int **map, t_raycaster ray, t_point *map_pos);
int						wolfenstein(t_mlx *mlx);
int						compare_nodes(t_node *s1, t_node *s2);
int						in_set(t_node **set, t_node *node);

long					time_between_frames(void);

double					calc_wall_distance(t_player *player, int side, t_raycaster ray);
double					to_radians(double degrees);

void					add_node(t_node **set, t_node *node);
void					calculate_relative_positions(t_mlx *mlx);
void					draw_object(t_mlx *mlx, t_texture *texture,
						int x, t_draw draw);
void					find_path(t_node **openSet, t_node **closedSet,
						t_node **path, t_node *end);
void					fire_gun(t_mlx *mlx, t_texture *gun, int size, long ms);
void					info(t_mlx *mlx);
void					init_level(t_mlx *mlx, char *file);
void					init_pathfinding(t_mlx *mlx);
void					init_wolf(char *map);
void					join_threads(int i, pthread_t *threads);
void					mini_map(t_player *player, int **map);
void					move_enemy(t_mlx *mlx);
void					move_player(t_mlx *mlx);
void					multiply_vector(double m, t_dpoint *vector);
void					player_look(t_player *player, t_controls *controls);
void					put_pixel(int x, int y, t_mlx *mlx, t_colour colour);;
void					rm_node(t_node **set, t_node *node);
void					rotate(t_mlx *mlx, double degrees);
void					rotate_vector(t_dpoint *vector, double rad);
void					set_player_angle(t_player *player, double degrees);
void					set_sprite_width(int *start, int *end, t_dpoint *location);
void					set_wall_height(int *draw_start, int *draw_end,
						int line_height);
void					spritecaster(t_mlx *mlx);

void					*raycaster(void *data);

t_point					calc_step_dir(t_player *player, t_raycaster ray, t_dpoint *side_dist);

t_dpoint				add_vector(t_dpoint *a, t_dpoint *b);
t_dpoint				get_unit_x(double rot);
t_dpoint				get_unit_y(double rot);
t_dpoint				set_raydir(int x, t_player *player);
t_dpoint				sub_vector(t_dpoint *a, t_dpoint *b);

t_texture				*get_textures(char *file);

#endif
