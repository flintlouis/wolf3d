# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fhignett <fhignett@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/18 12:32:22 by fhignett       #+#    #+#                 #
#    Updated: 2019/06/04 15:30:33 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

LIBFTO = libft/*.o
PRINTFO = printf/*.o
NAME = printflibft.a

all: $(NAME)

$(NAME):
	@make -C libft
	@make -C printf
	@ar rcs $(NAME) $(PRINTFO) $(LIBFTO)
	@make clean

clean:
	@make clean -C libft
	@make clean -C printf

fclean: clean
	@make fclean -C libft
	@make fclean -C printf
	@rm -f $(NAME)

re: fclean all
