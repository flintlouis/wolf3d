#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h> // voor testen ff

# define MEM(x) 		(x*)ft_memalloc(sizeof(x))
# define WIDTH			1200
# define HEIGHT			800
# define THREAD			12
# define MAP			mlx->map
# define PLAYER			mlx->player
# define CONTROLS		mlx->controls
# define TEXTURES		mlx->textures

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

typedef struct			s_colour
{
	t_byte				r;
	t_byte				g;
	t_byte				b;
	t_byte				opacity;
}						t_colour;

typedef struct			s_dpoint
{
	double				x;
	double				y;
}						t_dpoint;

typedef struct			s_texture
{
	int					width;
	int					height;
	t_colour			**colours;
}						t_texture;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_player
{
	t_dpoint			pos;
	t_dpoint			looking_dir;
	t_dpoint			plane;
}						t_player;

typedef struct			s_controls
{
	char				run:1;
	char				front:1;
	char				back:1;
	char				left:1;
	char				right:1;
	char				look_left:1;
	char				look_right:1;
}						t_controls;

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
	int					**map;
	t_player			*player;
	t_controls			*controls;
	t_texture			*textures;
}						t_mlx;

int						close_window(void *ptr);
int						key_press(int key, t_mlx *mlx);
int						key_release(int key, t_mlx *mlx);
int						mouse_move(int x, int y, t_mlx *mlx);
int						**get_map(char *file);
int						wolfenstein(t_mlx *mlx);
int						frames(void);
long					time_between_frames(void);
void					player_look(t_mlx *mlx);
void					move_player(t_mlx *mlx);
void					init_wolf(char *map);
void					draw_ver_line(t_mlx *mlx, t_point a, t_point b, t_colour colour); /* Only for colour walls */
void					draw_texture(t_mlx *mlx, int *draw_pos, int wall_height, int texture, int side, int x, int texture_x); /* For texture */
void					put_pixel(int x, int y, t_mlx *mlx, t_colour colour);;
void					rotate(t_mlx *mlx, double degrees);
void					*raycaster(void *data);
t_texture				*load_textures(void);

#endif