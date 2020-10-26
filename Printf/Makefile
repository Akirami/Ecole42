NAME = libftprintf.a
SRCS = \
	srcs/ft_printf.c \
	srcs/new_struct.c \
	srcs/parse_int.c \
	srcs/parse_str.c \
	srcs/parse_unsigned.c \
	srcs/parse_alpha.c \
	srcs/utils_and_write.c \
	srcs/set_args.c \

SRCS2 = \
	libft/ft_memset.c \
	libft/ft_bzero.c \
	libft/ft_memcpy.c \
	libft/ft_memccpy.c \
	libft/ft_memmove.c \
	libft/ft_memchr.c \
	libft/ft_memcmp.c \
	libft/ft_strlen.c \
	libft/ft_strdup.c \
	libft/ft_strcpy.c \
	libft/ft_strncpy.c \
	libft/ft_strcat.c \
	libft/ft_strncat.c \
	libft/ft_strlcat.c \
	libft/ft_strchr.c \
	libft/ft_strrchr.c \
	libft/ft_strstr.c \
	libft/ft_strnstr.c \
	libft/ft_strcmp.c \
	libft/ft_strncmp.c \
	libft/ft_atoi.c \
	libft/ft_isalpha.c \
	libft/ft_isdigit.c \
	libft/ft_isalnum.c \
	libft/ft_isascii.c \
	libft/ft_isprint.c \
	libft/ft_toupper.c \
	libft/ft_tolower.c \
	libft/ft_memalloc.c \
	libft/ft_memdel.c \
	libft/ft_strnew.c \
	libft/ft_strdel.c \
	libft/ft_strclr.c \
	libft/ft_striter.c \
	libft/ft_striteri.c \
	libft/ft_strmap.c \
	libft/ft_strmapi.c \
	libft/ft_strequ.c \
	libft/ft_strnequ.c \
	libft/ft_strsub.c \
	libft/ft_strjoin.c \
	libft/ft_strtrim.c \
	libft/ft_strsplit.c \
	libft/ft_itoa.c \
   	libft/ft_putchar.c \
	libft/ft_putstr.c \
	libft/ft_putendl.c \
	libft/ft_putnbr.c \
	libft/ft_putchar_fd.c \
	libft/ft_putstr_fd.c \
	libft/ft_putendl_fd.c \
	libft/ft_putnbr_fd.c \
	libft/ft_lstnew.c \
	libft/ft_lstdelone.c \
	libft/ft_lstdel.c \
	libft/ft_lstadd.c \
	libft/ft_lstiter.c \
	libft/ft_lstmap.c \
	libft/get_next_line.c \

LFT_PATH = ./libft/

OBJS = ${SRCS:.c=.o}
OBJS2 = ${SRCS2:.c=.o}
CC = gcc
AR = ar rcs
RM = rm -f
HEADER = includes/ft_printf.h
LIBFT_HEADER = libft/includes/libft.h
INC_HEAD = -I./$(HEADER) -I/$(LIBFT_HEADER)
CFLAGS =  -Wall -Wextra -Werror $(INC_HEAD)
DFLAGS =  -g3 -fsanitize=address

%.o:%.c	
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
${NAME}:	${OBJS} $(OBJS2)
	@make -C $(LFT_PATH)
#	@$(CC) $(LIBS) ${DFLAGS} -o $@ $^
	${AR} $(NAME) ${OBJS} ${OBJS2}

all:	${NAME}
bonus:	${NAME}
clean:
	@make -C $(LFT_PATH) clean
	${RM} ${OBJS}
fclean: clean 
	@make -C $(LFT_PATH) fclean
	${RM} ${NAME}
re : fclean all
.PHONY : re fclean all clean bonus
