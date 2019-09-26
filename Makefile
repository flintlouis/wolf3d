# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fhignett <fhignett@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/04 14:19:05 by fhignett       #+#    #+#                 #
#    Updated: 2019/09/26 17:42:04 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
INCL = -Iincludes -Iminilibx_macos -Ilibft/includes
LIB = -Lminilibx_macos -lmlx libft/printflibft.a
FRAMEWORK = -framework OpenGL -framework AppKit
CFILES = draw gun info init_node init keys_conf load_level load_textures main\
minimap move_enemy move_player nodes path_finding ray_info raycaster rotation\
sprite_info spritecaster time vectors wolfenstein errors
SOURCE = $(CFILES:%=source/%.c)
OFILES = $(SOURCE:source/%.c=.objects/%.o)
FLAGS = -Wall -Werror -Wextra -O2 -funroll-loops

all: $(NAME)

$(NAME): libft/printflibft.a $(OFILES)
	@gcc -o $(NAME) $(OFILES) $(LIB) $(INCL) $(FRAMEWORK) $(FLAGS)
	@echo "Done"

libft/printflibft.a:
	@make -C libft

.objects/%.o: source/%.c includes/wolf3d.h
	@echo "Compiling: $<"
	@gcc -o $@ -c $< $(INCL) $(FLAGS)

clean:
	@make clean -C libft/
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "Cleaning..."

re: fclean all