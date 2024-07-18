CC = cc
FLAGS = -Wall -Wextra -Werror -I ~/brew/opt/readline/include
LIBS =  -L ~/brew/opt/readline/lib -lreadline
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
GNL_DIR = get_next_line/
GNL = $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
GNL_HEADER = $(GNL_DIR)get_next_line.h

NAME = minishell
MINISHELL_HEADER = $(HEADER_DIR)minishell.h
HEADER_DIR = mandatory/includes/
BONUS_HEADER_DIR = bonus/includes/
RL_HEADER_DIR =  ~/brew/opt/readline/include/

#			PARSING				#
PARSE_HEADER = $(HEADER_DIR)parsing.h
PARSE_SRC_DIR = mandatory/parsing/src/
PARSE_OBJ_DIR = mandatory/parsing/obj/
PARSING_FILES = main.c parse.c functions_one.c functions_two.c \
				functions_three.c functions_four.c utils.c str.c \
				wildcard2.c variable_utils.c wildcard.c variable.c \
				variable_utils_2.c variable_utils_3.c wildcard_str.c \
				variables_wildcard.c wildcard_utils.c
PARSING_SRC = $(addprefix $(PARSE_SRC_DIR), $(PARSING_FILES))
PARSING_OBJ = $(addprefix $(PARSE_OBJ_DIR), $(PARSING_FILES:.c=.o))

#			EXECUTION			#
EXEC_HEADER = $(HEADER_DIR)execution.h
EXEC_SRC_DIR = mandatory/execution/src/
EXEC_OBJ_DIR = mandatory/execution/obj/
EXECUTION_FILES = 	define_priority.c execution.c ft_export.c \
					builtin.c ft_echo.c ft_pwd.c exec_utils1.c \
					redirections.c ft_env.c first_priority.c exec_utils2.c \
					ft_cd.c ft_unset.c ft_exit.c execution_2.c ft_heredoc.c \
					
EXECUTION_SRC = $(addprefix $(EXEC_SRC_DIR), $(EXECUTION_FILES))
EXECUTION_OBJ = $(addprefix $(EXEC_OBJ_DIR), $(EXECUTION_FILES:.c=.o))

NAME_BONUS = minishell_bonus
BONUS_HEADER_DIR = bonus/includes/
MINISHELL_HEADER_BONUS = $(BONUS_HEADER_DIR)minishell_bonus.h

#			PARSING_BONUS				#
PARSE_BONUS_HEADER = $(BONUS_HEADER_DIR)parsing_bonus.h
PARSE_BONUS_SRC_DIR = bonus/parsing/src/
PARSE_BONUS_OBJ_DIR = bonus/parsing/obj/
PARSING_BONUS_FILES = main_bonus.c parse_bonus.c functions_one_bonus.c functions_two_bonus.c \
				functions_three_bonus.c functions_four_bonus.c utils_bonus.c str_bonus.c \
				wildcard2_bonus.c variable_utils_bonus.c wildcard_bonus.c variable_bonus.c \
				variable_utils_2_bonus.c variable_utils_3_bonus.c wildcard_str_bonus.c \
				variables_wildcard_bonus.c wildcard_utils_bonus.c
PARSING_BONUS_SRC = $(addprefix $(PARSE_BONUS_SRC_DIR), $(PARSING_BONUS_FILES))
PARSING_BONUS_OBJ = $(addprefix $(PARSE_BONUS_OBJ_DIR), $(PARSING_BONUS_FILES:.c=.o))

#			EXECUTION_BONUS			#
EXEC_BONUS_HEADER = $(BONUS_HEADER_DIR)execution_bonus.h
EXEC_BONUS_SRC_DIR = bonus/execution/src/
EXEC_BONUS_OBJ_DIR = bonus/execution/obj/
EXECUTION_BONUS_FILES = define_priority_bonus.c execution_bonus.c ft_export_bonus.c \
					builtin_bonus.c ft_echo_bonus.c ft_pwd_bonus.c exec_utils1_bonus.c \
					redirections_bonus.c ft_env_bonus.c first_priority_bonus.c exec_utils2_bonus.c \
					ft_cd_bonus.c ft_unset_bonus.c ft_exit_bonus.c execution_2_bonus.c ft_heredoc_bonus.c \
					
EXECUTION_BONUS_SRC = $(addprefix $(EXEC_BONUS_SRC_DIR), $(EXECUTION_BONUS_FILES))
EXECUTION_BONUS_OBJ = $(addprefix $(EXEC_BONUS_OBJ_DIR), $(EXECUTION_BONUS_FILES:.c=.o))

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

$(PARSE_OBJ_DIR):
	@mkdir -p $(PARSE_OBJ_DIR)

$(EXEC_OBJ_DIR):
	@mkdir -p $(EXEC_OBJ_DIR)

$(NAME): $(PARSING_OBJ) $(EXECUTION_OBJ) $(GNL)
	@$(CC) $(FLAGS) $(LIBS) $(PARSING_OBJ) $(EXECUTION_OBJ) $(LIBFT) $(GNL) -o $(NAME)
	@echo "$(CYAN)$(BOLD)Minishell Created Succefully √$(RESET)"

$(PARSE_OBJ_DIR)%.o: $(PARSE_SRC_DIR)%.c $(PARSE_HEADER) $(MINISHELL_HEADER)
	$(update_progress)
	@$(CC) $(FLAGS) -I $(RL_HEADER_DIR) -I $(HEADER_DIR) -I $(GNL_DIR) -I $(LIBFT_DIR) -c $< -o $@

$(EXEC_OBJ_DIR)%.o: $(EXEC_SRC_DIR)%.c $(EXEC_HEADER) $(MINISHELL_HEADER)
	$(update_progress)
	@$(CC) $(FLAGS) -I $(HEADER_DIR) -I $(GNL_DIR) -I $(LIBFT_DIR) -c $< -o $@

bonus: $(LIBFT) $(PRINTF) $(PARSE_BONUS_OBJ_DIR) $(EXEC_BONUS_OBJ_DIR) $(NAME_BONUS) thanks

$(PARSE_BONUS_OBJ_DIR):
	@mkdir -p $(PARSE_BONUS_OBJ_DIR)

$(EXEC_BONUS_OBJ_DIR):
	@mkdir -p $(EXEC_BONUS_OBJ_DIR)

$(NAME_BONUS): $(PARSING_BONUS_OBJ) $(EXECUTION_BONUS_OBJ) $(GNL)
	@$(CC) $(FLAGS) $(LIBS) $(PARSING_BONUS_OBJ) $(EXECUTION_BONUS_OBJ) $(LIBFT) $(GNL) -o $(NAME_BONUS)
	@echo "$(CYAN)$(BOLD)Minishell Created Succefully √$(RESET)"

$(PARSE_BONUS_OBJ_DIR)%.o: $(PARSE_BONUS_SRC_DIR)%.c $(PARSE_BONUS_HEADER) $(MINISHELL_HEADER_BONUS)
	$(update_progress)
	@$(CC) $(FLAGS) -I $(RL_HEADER_DIR) -I $(BONUS_HEADER_DIR) -I $(GNL_DIR) -I $(LIBFT_DIR) -c $< -o $@

$(EXEC_BONUS_OBJ_DIR)%.o: $(EXEC_BONUS_SRC_DIR)%.c $(EXEC_BONUS_HEADER) $(MINISHELL_HEADER_BONUS)
	$(update_progress)
	@$(CC) $(FLAGS) -I $(BONUS_HEADER_DIR) -I $(GNL_DIR) -I $(LIBFT_DIR) -c $< -o $@

clean:
	@echo "$(RED)$(BOLD)Objects Deleting √$(RESET)"
	@rm -f $(PARSING_OBJ) $(EXECUTION_OBJ) $(PARSING_BONUS_OBJ) $(EXECUTION_BONUS_OBJ)
	@rm -rf $(PARSE_OBJ_DIR) $(EXEC_OBJ_DIR) $(PARSE_BONUS_OBJ_DIR) $(EXEC_BONUS_OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)$(BOLD)Binary Deleted   √$(RESET)"
	@rm -f $(NAME) $(NAME_BONUS)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all thanks bonus clean fclean re $(LIBFT) $(PRINTF)
