CC = cc
FLAGS = -L libs/ -lreadline -g -fsanitize=address #-Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBFT_DIR = libft/
GNL_DIR = get_next_line/
GNL = $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
GNL_HEADER = $(GNL_DIR)get_next_line.h

NAME = minishell
HEADER_DIR = mandatory/includes/
BONUS_HEADER_DIR = bonus/includes/

#			PARSING				#
PARSE_HEADER = $(HEADER_DIR)parsing.h
PARSE_SRC_DIR = mandatory/parsing/src/
PARSE_OBJ_DIR = mandatory/parsing/obj/
PARSING_FILES = main.c parse.c functions.c utils.c str.c exec_draft.c pipex_draft.c
PARSING_SRC = $(addprefix $(PARSE_SRC_DIR), $(PARSING_FILES))
PARSING_OBJ = $(addprefix $(PARSE_OBJ_DIR), $(PARSING_FILES:.c=.o))

#			EXECUTION			#
EXEC_HEADER = $(HEADER_DIR)execution.h
EXEC_SRC_DIR = mandatory/execution/src/
EXEC_OBJ_DIR = mandatory/execution/obj/
# EXECUTION_FILES = executor.c ft_cd.c ft_echo.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c main.c utils.c
EXECUTION_SRC = $(addprefix $(EXEC_SRC_DIR), $(EXECUTION_FILES))
EXECUTION_OBJ = $(addprefix $(EXEC_OBJ_DIR), $(EXECUTION_FILES:.c=.o))

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

all: $(LIBFT) $(PARSE_OBJ_DIR) $(EXEC_OBJ_DIR) $(NAME)

$(LIBFT): $(LIBFT_DIR)
	@make -C $<

$(PARSE_OBJ_DIR):
	mkdir -p $(PARSE_OBJ_DIR)

$(EXEC_OBJ_DIR):
	mkdir -p $(EXEC_OBJ_DIR)

$(NAME): $(PARSING_OBJ) $(EXECUTION_OBJ) $(LIBFT) $(GNL)
	@echo "$(BLUE)$(BOLD)Creating $(NAME) executable...$(RESET)"
	$(CC) $(FLAGS) $^ -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) created$(RESET)"

$(PARSE_OBJ_DIR)%.o: $(PARSE_SRC_DIR)%.c $(PARSE_HEADER)
	@echo "$(CYAN)$(BOLD)Compiling $<$(RESET)"
	$(CC) $(FLAGS) -I $(HEADER_DIR) -I $(GNL_DIR) -I $(LIBFT_DIR) -c $< -o $@

$(EXEC_OBJ_DIR)%.o: $(EXEC_SRC_DIR)%.c $(EXEC_HEADER)
	@echo "$(CYAN)$(BOLD)Compiling $<$(RESET)"
	$(CC) $(FLAGS) -I $(HEADER_DIR) -I $(GNL_DIR) -I $(LIBFT_DIR) -c $< -o $@

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
	rm -f $(PARSING_OBJ) $(EXECUTION_OBJ) $(BONUS_PARSING_OBJ) $(BONUS_EXECUTION_OBJ)
	make clean -C $(LIBFT_DIR)
	@echo "$(RED)$(BOLD)Object files removed$(RESET)"

fclean: clean
	rm -f $(NAME) $(BONUS)
	make fclean -C $(LIBFT_DIR)
	@echo "$(RED)$(BOLD)$(NAME) and $(BONUS) removed$(RESET)"

re: fclean all

.PHONY: all $(LIBFT) bonus clean fclean re