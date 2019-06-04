# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fhignett <fhignett@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/09 15:24:52 by fhignett       #+#    #+#                 #
#    Updated: 2019/04/18 14:25:12 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =  libftprintf.a
EXECUTABLE = ft_printf
FILESC = flags.c ft_printf.c get_data_list.c get_flags.c number_length.c \
print_binary.c print_char.c print_decimal.c print_float.c print_hex.c \
print_oct.c print_output.c print_pointer.c print_precision.c print_string.c \
print_unsigned.c print_width_extra.c print_width.c put_data.c
FILESO = $(FILESC:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc -c $(FLAGS) $(FILESC) -I ../includes/

clean:
	@rm -f $(FILESO)

fclean: clean
	@rm -f $(NAME)

re: fclean all
