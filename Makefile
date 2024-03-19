CC = cc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBFT_DIR = libft/
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNL_HEADER = get_next_line/get_next_line.h

NAME = minishell
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = $(SRC_DIR)minishell.h
FILES = main.c 
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

# BONUS = minishell_bonus
# BONUS_SRC_DIR = bonus/src/
# BONUS_OBJ_DIR = bonus/obj/
# BONUS_HEADER = $(BONUS_SRC_DIR)minishell_bonus.h
# BONUS_FILES = 
# BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(BONUS_FILES))
# BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_FILES:.c=.o))

RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
BLUE = \033[0;34m
BOLD = \033[1m
RESET = \033[0m

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(LIBFT): $(LIBFT_DIR)
	@make -C $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@echo "$(BLUE)$(BOLD)Creating $(NAME) executable...$(RESET)"
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) created$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@echo "$(CYAN)$(BOLD)Compiling $<$(RESET)"
	$(CC) $(FLAGS) -c $< -o $@

# bonus: $(LIBFT) $(BONUS_OBJ_DIR) $(BONUS)

# $(BONUS_OBJ_DIR):
# 	mkdir -p $(BONUS_OBJ_DIR)

# $(BONUS): $(BONUS_OBJ)
# 	@echo "$(BLUE)$(BOLD)Creating $(BONUS) executable...$(RESET)"
# 	$(CC) $(FLAGS) $(BONUS_OBJ) $(LIBFT) $(GNL) -o $(BONUS)
# 	@echo "$(GREEN)$(BOLD)$(BONUS) created$(RESET)"

# $(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(BONUS_HEADER) $(GNL_HEADER)
# 	@echo "$(CYAN)$(BOLD)Compiling $<$(RESET)"
# 	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	@echo "$(RED)$(BOLD)Object files removed$(RESET)"

fclean: clean
	rm -f $(NAME) $(BONUS)
	@echo "$(RED)$(BOLD)$(NAME) and $(BONUS) removed$(RESET)"

re: fclean all

.PHONY: all $(LIBFT) bonus clean fclean re