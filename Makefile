# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fhignett <fhignett@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/04 14:19:05 by fhignett       #+#    #+#                 #
#    Updated: 2019/10/07 11:05:52 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

GREEN = $(shell printf "\e[38;5;10m")
WHITE = $(shell printf "\e[39m")
RED = $(shell printf "\033[0;31m")
YELLOW = $(shell printf "\033[0;33m")
PLUS = $(shell printf '$(GREEN)[ + ]$(WHITE)')
MIN = $(shell printf '$(RED)[ - ]$(WHITE)')
DONE = $(shell printf '$(YELLOW)[ √ ]$(WHITE)')

NAME = wolf3d
INCL = -Iincludes -Iminilibx_macos -Ilibft/includes
LIB = -Lminilibx_macos -lmlx libft/printflibft.a
FRAMEWORK = -framework OpenGL -framework AppKit
SOURCE = draw gun info init_node init keys_conf load_level load_textures main \
minimap move_enemy move_player nodes path_finding ray_info raycaster rotation \
sprite_info spritecaster time vectors wolfenstein errors
CFILES = $(SOURCE:%=source/%.c)
OFILES = $(CFILES:source/%.c=.objects/%.o)
FLAGS = -Wall -Werror -Wextra
OPT = -O2 -funroll-loops

all: $(NAME)

$(NAME): libft/printflibft.a .objects $(OFILES)
	@gcc -o $(NAME) $(OFILES) $(LIB) $(INCL) $(FRAMEWORK) $(OPT) $(FLAGS)
	@echo "$(DONE) $(NAME)"

libft/printflibft.a:
	@make -C libft
	@echo "$(PLUS) printflibft.a"

.objects/%.o: source/%.c includes/wolf3d.h
	@gcc -o $@ -c $< $(INCL) $(OPT) $(FLAGS)
	@echo "$(PLUS) $@"

.objects:
	@mkdir .objects

clean:
	@make clean -C libft/
	@rm -f $(OFILES)
	@echo "$(MIN) object files removed"

fclean: clean
	@make fclean -C libft
	@echo "$(MIN) printflibft.a"
	@rm -f $(NAME)
	@echo "$(MIN) $(NAME)"

re: fclean all