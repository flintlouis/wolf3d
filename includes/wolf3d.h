#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "ft_printf.h"
# include <pthread.h>
# include <stdio.h> // voor testen ff
# include <stdlib.h> /* FOR MINIMAP */

# define MEM(x) 		(x*)ft_memalloc(sizeof(x))
# define WIDTH			1200
# define HEIGHT			800
# define THREAD			4
# define WALLCOUNT		5 // AMOUNT OF WALLS
# define OBJECTCOL		11 // AMOUNT OF OBJECTS WITH COLLISION
# define ENEMY			14 // ENEMY NUMBER ON MAP
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
	t_mapobject			**enemies;
}						t_mlx;

int						close_window(void *ptr);
int						frames(void);
int						key_press(int key, t_mlx *mlx);
int						key_release(int key, t_mlx *mlx);
int						mouse_move(int x, int y, t_mlx *mlx);
int						wolfenstein(t_mlx *mlx);

long					time_between_frames(void);

double					to_radians(double degrees);

void					draw_object(t_mlx *mlx, t_texture *texture, int x, t_draw draw);
void					init_wolf(char *map);
void					init_level(t_mlx *mlx, char *file);
void					join_threads(int i, pthread_t *threads);
void					move_player(t_mlx *mlx);
void					multiply_vector(double m, t_dpoint *vector);
void					player_look(t_player *player, t_controls *controls);
void					put_pixel(int x, int y, t_mlx *mlx, t_colour colour);;
void					rotate(t_mlx *mlx, double degrees);
void					rotate_vector(t_dpoint *vector, double rad);
void					set_player_angle(t_player *player, double degrees);
void					set_wall_height(int *draw_start, int *draw_end, int line_height);
void					spritecaster(t_mlx *mlx);

void					*raycaster(void *data);

t_dpoint				add_vector(t_dpoint *a, t_dpoint *b);
t_dpoint				get_unit_x(double rot);
t_dpoint				get_unit_y(double rot);
t_dpoint				sub_vector(t_dpoint *a, t_dpoint *b);

t_texture				*get_textures(char *file);

#endif