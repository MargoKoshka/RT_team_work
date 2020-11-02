# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/13 02:24:53 by wrhett            #+#    #+#              #
#    Updated: 2020/10/18 15:41:08 by wrhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

CC = gcc -g

OS = $(shell uname)

SRC_DIR = ./src/
SRC_LIST = main.c \
			ft_init_object.c \
			ft_init_object_light.c \
			scene_objects.c \
			ft_paint_objects.c \
			ft_raytrace_object.c \
			ft_raytrace_cylinder.c \
			ft_raytrace_cone.c \
			ft_raytrace_ring.c \
			ft_raytrace_hemisphere.c \
			check_intersect.c \
			ft_calculate_vector_normal.c \
			ft_calculate_vector_normal_1.c \
			ft_color_function.c \
			ft_calculate_color.c \
			ft_reflection_color.c \
			ft_refraction_color.c \
			ft_aliasing_effects.c \
			ft_operation_key.c ft_operation_mouse.c \
			ft_vector_function.c ft_vector_function_2.c \
			ft_init_function.c \
			ft_calculate_constant.c \
			ft_standard_methods.c ft_window_menu.c \
			ft_solve_quadratic_equation.c \
			textures.c \
			texture_generate.c \
			get_color.c

SRC = $(notdir $(SRC_LIST))
# SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJECTS_DIR = ./objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC))
OBJECTS = $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

HEADER_DIR = ./includes/
HEADER_LIST = rtv1.h structure.h menu.h key_linux.h key_macos.h events.h
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_LIST))

INCLUDES = -I $(HEADER_DIR) -I $(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBRARIES = $(LIBFT) $(MLX)

ifeq ($(OS), Linux)
	MLX_DIR = ./minilibx/
	MLX = -L ./minilibx/ -lmlx -lXext -lX11 -lm -lpthread -lz
else
	MLX_DIR = ./minilibx_macos/
	MLX = -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
endif

FLAGS = -Wall -Wextra -Werror -std=c99 -O3

vpath %.c ./src/
vpath %.c ./src/parsing/
vpath %.c ./src/raytrace_object/
# vpath %.c ./minilibx/
vpath %.h ./includes/

.PHONY: all clean fclean re FAKE

all: $(NAME)

$(NAME):$(LIBFT) $(OBJECTS_DIR) $(OBJECTS)
		@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBRARIES)
		@echo "\n✅\033[33m$(NAME):\033[32m was created\033[0m"

$(OBJECTS_DIR):
		@mkdir -p $(OBJECTS_DIR)
		@echo "\n✅\033[33m$(NAME):\033[32m $(OBJECTS_DIR)directory was created\033[0m"

$(OBJECTS_DIR)%.o: %.c $(HEADER)
		@$(CC) $(FLAGS) -c $(INCLUDES) -o $@ $<
		@echo "✅\c"

$(LIBFT): FAKE
		@$(MAKE) -C $(LIBFT_DIR)
		@$(MAKE) -C $(MLX_DIR)

clean:
		@rm -rf $(OBJECTS_DIR)
		@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
		@/bin/rm -f $(NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
# minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
# MLX = ./minilibx/libmlx.a -lXext -lX11 -lm // for linux GNU
# -L ../minilibx -lmlx -framework OpenGL -framework AppKit
# MLX = ./minilibx/libmlx.a -lXext -lX11 -lm // for linux GNU
# INCLUDES = -I$(HEADER_DIR) -I$(LIBFT_HEADERS) -I$(MINILIBX_HEADERS)
# $(CC) $(FLAGS) -c -I$(HEADERS_DIRECTORY) -o $@ $<
# $(CC) $(FLAGS) -MD -c $(INCLUDES) -o $@ $<
#-fsanitize=address
# $(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(INCLUDES) $(LIBRARIES)
#MLX = ../minilibx_macos/libmlx.a -L /path/to/lib libstuff.dylib OpenGL\
#  -L /path/to/lib libstuff.dylib AppKit
# MLX = $(MLX_DIR)libmlx.a -L /System/Library/Frameworks/OpenGL.framework\
	# 		-L /System/Library/Frameworks/AppKit.framework

# @echo "\033[32m.\033[0m\c"