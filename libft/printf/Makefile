# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fhignett <fhignett@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/09 15:24:52 by fhignett       #+#    #+#                 #
#    Updated: 2019/09/27 11:36:34 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =  libftprintf.a
EXECUTABLE = ft_printf
SOURCE = flags ft_printf get_data_list get_flags number_length \
print_binary print_char print_decimal print_float print_hex \
print_oct print_output print_pointer print_precision print_string \
print_unsigned print_width_extra print_width put_data
FILESC = $(SOURCE:%=%.c)
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
