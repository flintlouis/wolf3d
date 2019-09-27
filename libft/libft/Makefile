# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fhignett <fhignett@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/09 15:24:52 by fhignett       #+#    #+#                 #
#    Updated: 2019/09/27 11:45:36 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SOURCE = ft_putnbr ft_putchar ft_putstr ft_putendl ft_putnbr_fd ft_putchar_fd \
ft_putstr_fd ft_putendl_fd ft_bzero ft_memdel ft_strdel ft_strclr ft_striter \
ft_striteri ft_memset ft_memcpy ft_memccpy ft_memmove ft_memchr ft_memalloc \
ft_strdup ft_strchr ft_strrchr ft_strstr ft_strnstr ft_strcpy ft_strncpy \ft_strcat \
ft_strncat ft_strnew ft_strmap ft_strmapi ft_strsub ft_strjoin ft_strtrim \
ft_itoa ft_strsplit ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
ft_toupper ft_tolower ft_atoi ft_strcmp ft_strncmp ft_memcmp ft_strequ \
ft_strnequ ft_strlen ft_strlcat ft_lstnew ft_lstdelone ft_lstdel ft_lstadd \
ft_lstiter ft_lstmap ft_countwords ft_print_byte ft_sort_int_tab \
ft_lstadd_back ft_strsplit_list ft_lstinsert ft_lstfold ft_power \
ft_get_next_line ft_sqrt ft_atoi_base ft_itoa_base ft_free_2darray ft_clamp \
ft_intlen ft_putunsigned ft_map ft_wait ft_milsec ft_min ft_max
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
