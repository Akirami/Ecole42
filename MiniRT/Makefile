NAME = miniRT
SRCS = \
	srcs/main.c \
	srcs/main_loop.c \
	srcs/parsing/get_file_data.c \
	srcs/parsing/get_cam_amb_data.c \
	srcs/parsing/get_sp_data.c \
	srcs/parsing/get_li_data.c \
	srcs/parsing/get_cy_data.c \
	srcs/parsing/get_tr_data.c \
	srcs/parsing/get_sq_data.c \
	srcs/parsing/get_co_data.c \
	srcs/parsing/get_bonus_data.c \
	srcs/parsing/parse_utils.c \
	srcs/init_stuff.c \
	srcs/util_rotate.c \
	srcs/util_vec.c \
	srcs/util_vec2.c \
	srcs/utils2.c \
	srcs/utils3.c \
	srcs/prepare_stuff.c \
	srcs/draw/draw_spheres.c \
	srcs/draw/draw_plan.c \
	srcs/draw/draw_scene.c \
	srcs/draw/draw_square.c \
	srcs/draw/draw_triangles.c \
	srcs/draw/draw_cylinders.c \
	srcs/draw/draw_cubes.c \
	srcs/draw/draw_hud.c \
	srcs/draw/draw_cones.c \
	srcs/key_events.c \
	srcs/load_textures.c \
	srcs/prepare_thread.c \
	srcs/calc_light.c \
	srcs/bmp.c \

RES_X := $(shell osascript -e 'tell application "Finder" to get bounds of window of desktop' | cut -d , -f 3 | cut -c 2-)
RES_Y := $(shell osascript -e 'tell application "Finder" to get bounds of window of desktop' | cut -d , -f 4 | cut -c 2-)
OBJS = ${SRCS:.c=.o}
OBJS2 = ${SRCS2:.c=.o}
CC := clang
AR := ar rcs
RM := rm -f
HEADER = ./includes/minirt.h
LFT_PATH = ./3rdparty/libft/
FT = -L$(LFT_PATH) -lft
MLX_PATH = ./3rdparty/minilibx/
MLX = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
INC_HEAD = -I./$(HEADER)
CFLAGS =  -Wall -Wextra -g $(INC_HEAD)
DEFFLAG = -D RES_X=${RES_X} -D RES_Y=${RES_Y}
LDFLAGS =  -fsanitize=address

%.o:%.c	
		${CC} ${DEFFLAG} ${CFLAGS} -c $< -o ${<:.c=.o}
${NAME}:	${OBJS}
#	@make -C $(LFT_PATH)
#	@make -C $(MLX_PATH)
	${CC} ${OBJS} $(FT) $(MLX) -o $(NAME)

all:	${NAME}
clean:
#	@make -C $(LFT_PATH) clean
#	@make -C $(MLX_PATH) clean
	${RM} ${OBJS}
fclean: clean 
#	@make -C $(LFT_PATH) fclean
#	@make -C $(MLX_PATH) clean
	${RM} ${NAME}
re : fclean all
.PHONY : re fclean all clean bonus
