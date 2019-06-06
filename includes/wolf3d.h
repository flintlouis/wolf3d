#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "ft_printf.h"

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

# define MEM(x) 		(x*)ft_memalloc(sizeof(x))
# define WIDTH			1200
# define HEIGHT			800

typedef unsigned char	t_byte;

typedef struct			s_map
{
	int					height;
	int					width;
	int					**map;
}						t_map;

typedef struct			s_colour
{
	t_byte				r;
	t_byte				g;
	t_byte				b;
}						t_colour;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_map				*map;
}						t_mlx;

int						close_window(void *ptr);
int						key_press(int key, t_mlx *mlx);
int						key_release(int key, t_mlx *mlx);
void					init_wolf(char *map);
t_map					*get_map(char *file);

#endif