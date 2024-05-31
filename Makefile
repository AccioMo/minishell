CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -I ~/brew/opt/readline/include
LIBS =  -L ~/brew/opt/readline/lib -lreadline
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
GNL_DIR = get_next_line/
GNL = $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
GNL_HEADER = $(GNL_DIR)get_next_line.h
PRINTF_DIR = printf/
PRINTF = $(PRINTF_DIR)libftprintf.a

NAME = minishell
HEADER_DIR = mandatory/includes/
BONUS_HEADER_DIR = bonus/includes/
RL_HEADER_DIR =  ~/brew/opt/readline/include/

#			PARSING				#
PARSE_HEADER = $(HEADER_DIR)parsing.h
PARSE_SRC_DIR = mandatory/parsing/src/
PARSE_OBJ_DIR = mandatory/parsing/obj/
PARSING_FILES = main.c parse.c functions_one.c functions_two.c functions_three.c utils.c str.c
PARSING_SRC = $(addprefix $(PARSE_SRC_DIR), $(PARSING_FILES))
PARSING_OBJ = $(addprefix $(PARSE_OBJ_DIR), $(PARSING_FILES:.c=.o))

#			EXECUTION			#
EXEC_HEADER = $(HEADER_DIR)execution.h
EXEC_SRC_DIR = mandatory/execution/src/
EXEC_OBJ_DIR = mandatory/execution/obj/
EXECUTION_FILES = 	define_priority.c wildcard.c execution.c ft_export.c \
					builtin.c ft_echo.c variable.c ft_pwd.c exec_utils1.c \
					redirections.c ft_env.c first_priority.c exec_utils2.c \
					ft_cd.c ft_unset.c variable_utils.c ft_exit.c
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
BLACK = \033[30m
WHITE_BG = \033[47m
UP = \033[A

TOTAL_FILES = $(words $(PARSING_FILES) $(EXECUTION_FILES))
COMPILED_COUNT = 0

define update_progress
	@bash -c 'if [ $(COMPILED_COUNT) -eq 0 ]; then echo; fi;'
	$(eval COMPILED_COUNT=$(shell echo $$(($(COMPILED_COUNT) + 1))))
	$(eval PERCENT=$(shell echo $$(($(COMPILED_COUNT) * 100 / $(TOTAL_FILES)))))
	@bash -c 'echo -e "$(UP)\r$(GREEN)$(BOLD)[$(PERCENT)%] Compiling Minishell...$(RESET)"'
endef

all: $(LIBFT) $(PRINTF) $(PARSE_OBJ_DIR) $(EXEC_OBJ_DIR) $(NAME) thanks

thanks:
	@echo "$(BLACK)$(WHITE_BG)$(BOLD)Compilation complete.$(RESET)"

$(LIBFT): $(LIBFT_DIR)
	@make -sC $<

$(PRINTF): $(PRINTF_DIR)
	@make -sC $<

$(PARSE_OBJ_DIR):
	@mkdir -p $(PARSE_OBJ_DIR)

$(EXEC_OBJ_DIR):
	@mkdir -p $(EXEC_OBJ_DIR)

$(NAME): $(PARSING_OBJ) $(EXECUTION_OBJ) $(GNL)
	@$(CC) $(FLAGS) $(LIBS) $(PARSING_OBJ) $(EXECUTION_OBJ) $(LIBFT) $(PRINTF) $(GNL) -o $(NAME)
	@echo "$(CYAN)$(BOLD)Minishell Created Succefully √$(RESET)"

$(PARSE_OBJ_DIR)%.o: $(PARSE_SRC_DIR)%.c $(PARSE_HEADER)
	$(update_progress)
	@$(CC) $(FLAGS) -I $(RL_HEADER_DIR) -I $(HEADER_DIR) -I $(GNL_DIR) -I $(LIBFT_DIR) -I $(PRINTF_DIR) -c $< -o $@

$(EXEC_OBJ_DIR)%.o: $(EXEC_SRC_DIR)%.c $(EXEC_HEADER)
	$(update_progress)
	@$(CC) $(FLAGS) -I $(HEADER_DIR) -I $(GNL_DIR) -I $(LIBFT_DIR) -I $(PRINTF_DIR) -c $< -o $@

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
	@echo "$(RED)$(BOLD)Objects Deleting √$(RESET)"
	@rm -f $(PARSING_OBJ) $(EXECUTION_OBJ) $(BONUS_PARSING_OBJ) $(BONUS_EXECUTION_OBJ)
	@rm -rf $(PARSE_OBJ_DIR) $(EXEC_OBJ_DIR) $(BONUS_OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)
#	@rmdir printf/obj/

fclean: clean
	@echo "$(RED)$(BOLD)Binary Deleted   √$(RESET)"
	@rm -f $(NAME) $(BONUS)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all thanks bonus clean fclean re $(LIBFT) $(PRINTF)
