SRC =	main.c			\
		change_image.c	\
		color.c			\
		ft_atof.c		\
		ft_atosign.c	\
		julia.c			\
		key_hook.c		\
		mandelbrot.c	\
		mouse_hook.c	\
		parsing.c		\
		vela.c			\
		threads.c		\
		
TARGET = fractol
OBJDIR = objs
SRCDIR = src
INCLUDE_DIR = include

INC := -I $(INCLUDE_DIR)

OBJ = $(addprefix objs/, $(SRC:.c=.o))

MLX = ./MLX42/
MLX_LIB = $(addprefix $(MLX), libmlx42.a)
MLX_INC = -I ./MLX42/include
CFLAGS = -Wall -Werror -Wextra -pthread -Ofast $(INC)
# -fsanitize=address -g
# -fsanitize=thread -g

all: $(TARGET)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLXFLAGS = -ldl -lglfw
else ifeq ($(UNAME_S), Darwin)
	MLXFLAGS = -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/
endif

$(TARGET): $(OBJ)
	@make -C MLX42
	@echo "Compiling main executable"
	@$(CC) $(OBJ) $(CFLAGS) $(INC) $(MLX_INC) $(MLX_LIB) $(MLXFLAGS) -lm -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDE_DIR)/fractol.h
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(INC) $(MLX_INC) -c -o $@ $<

mandelbrot: all
	./$(TARGET) mandelbrot

vela: all
	./$(TARGET) vela

clean:
	@echo Cleaning Object Files
	@make -C MLX42 clean
	@rm -f $(OBJ)

fclean: clean
	@echo Cleaning All Remaining Files
	@make -C MLX42 fclean
	@rm -f $(TARGET)
	@rm -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re bonus