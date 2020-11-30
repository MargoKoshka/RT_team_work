NAME = RT

CC = gcc -g

OS = $(shell uname)

SRC_DIR = ./src/
SRC_LIST = main.c\
			ft_paint_objects.c\
			ft_raytrace_object.c\
			ft_raytrace_cylinder.c\
			ft_raytrace_cone.c\
			ft_raytrace_ring.c\
			ft_raytrace_hemisphere.c\
			ft_raytrace_paraboloid.c\
			check_intersect.c\
			ft_calculate_vector_normal.c\
			ft_calculate_vector_normal_1.c\
			ft_color_function.c\
			ft_calculate_color.c\
			ft_reflection_color.c\
			ft_refraction_color.c\
			ft_aliasing_effects.c\
			ft_operation_key.c  ft_operation_key_1.c ft_operation_mouse.c\
			ft_operation_key_2.c\
			ft_screenshot_bmp.c ft_screenshot_ppm.c\
			ft_vector_function.c ft_vector_function_2.c\
			ft_standard_methods.c free_memory.c ft_window_menu.c\
			ft_solve_quadratic_equation.c\
			read_file.c\
			check_file.c\
			tools_read.c\
			errors.c\
			malloc_free.c\
			parsing_lights.c\
			parsing_objects.c\
			parsing.c\
			tools_lights.c\
			tools_objects.c\
			tools.c\
			ft_calculate_constant.c\
			ft_object_data.c\
			textures.c\
			texture_generate.c\
			get_color.c\
			filters.c\
			sepia.c\
			perlin_support.c\
			textura2.c\
			anaglyph_mb.c\
			loading.c\
			textura3.c\
			textura4.c\
			ft_calculate_color2.c\
			parsing_objects2.c\
			tools_objects2.c\
			ft_window_menu2.c\
			ft_calculate_color3.c

SRC = $(notdir $(SRC_LIST))

OBJECTS_DIR = ./objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC))
OBJECTS = $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

HEADER_DIR = ./includes/
HEADER_LIST = rt.h structure.h menu.h key_linux.h key_macos.h events.h parsing.h
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_LIST))

INCLUDES = -I $(HEADER_DIR) -I $(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBRARIES = $(LIBFT) $(MLX)

SCREEN_DIR = ./screen_scenes/

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
vpath %.c ./src/parsing_prev/
vpath %.c ./src/raytrace_object/
vpath %.c ./src/service_functions/
vpath %.c ./src/effects/
vpath %.c ./src/operation/
vpath %.c ./src/textura
vpath %.h ./includes/

.PHONY: all clean fclean re FAKE

all: $(NAME)

$(NAME):$(LIBFT) $(OBJECTS_DIR) $(OBJECTS) $(SCREEN_DIR)
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

$(SCREEN_DIR):
		@mkdir -p $(SCREEN_DIR)
		@echo "\n✅\033[33m$(NAME):\033[32m $(SCREEN_DIR)directory was created\033[0m"

clean:
		@rm -rf $(OBJECTS_DIR)
		@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
		@/bin/rm -f $(NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean
		@rm -rf $(SCREEN_DIR)

re: fclean all

cleanscreen:
		@rm -rf $(SCREEN_DIR)
