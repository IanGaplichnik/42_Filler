CC = gcc
NAME = igaplich.filler
FLAGS =-g -Wall -Wextra #-fsanitize=address

SRC_DIR = ./src/
SRC_FILES = main.c \
	utils.c \
	map.c \
	piece.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = ./includes/
INC_FILES = filler.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))

LIBPRINT_DIR = libft/
LIBPRINT = libftprintf.a

compile:
	$(CC) -g $(FLAGS) src/*.c -o $(NAME)

all : $(NAME)

$(NAME): $(OBJ) 
	@make -C ./libft
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ)  -L. libft/libftprintf.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c clean
	@mkdir $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@make -C ./libft clean
	@rm -rf $(OBJ_DIR)

fclean : clean
	@make -C ./libft fclean
	@rm -f $(NAME)

re : fclean all clean all
