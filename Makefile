# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fhignett <fhignett@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/04 14:19:05 by fhignett       #+#    #+#                 #
#    Updated: 2019/08/06 13:45:15 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
INCL = -Iincludes -Iminilibx_macos -Ilibft/includes
LIB = -Lminilibx_macos -lmlx libft/printflibft.a
FRAMEWORK = -framework OpenGL -framework AppKit
CFILES = *
SOURCE = $(CFILES:%=source/%.c)
OFILES = $(SOURCE:.c=.o) # HEBBEN WE DIT NODIG???
FLAGS = -Wall -Werror -Wextra # ADD LATER -O2

all: $(NAME)

$(NAME):
		@echo "Compiling..."
		@make -C libft
		@gcc -o $(NAME) $(SOURCE) $(LIB) $(INCL) $(FRAMEWORK) -O2
		@make clean
		@echo "Done"

clean:
		@make clean -C libft/

fclean: clean
		@rm -f $(NAME)
		@make fclean -C libft
		@echo "Cleaning..."

re: fclean all