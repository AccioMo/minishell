NAME = libftprintf.a
HEADER = ft_printf.h
CC = cc
CFLAGS = -Werror -Wextra -Werror
SRC_DIR = src/
OBJ_DIR = obj/

FILES = ft_printf.c ft_printf_putchar.c ft_printf_putstr.c ft_printf_puthex.c ft_printf_putadr.c ft_printf_nbr.c ft_printf_putunsigned.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CYAN = \033[0;36m
BOLD = \033[1m
UP = \033[1A

TOTAL_FILES := $(words $(FILES))
COMPILED_COUNT := 0

define update_progress
	$(eval COMPILED_COUNT=$(shell echo $$(($(COMPILED_COUNT) + 1))))
	$(eval PERCENT=$(shell echo $$(($(COMPILED_COUNT) * 100 / $(TOTAL_FILES)))))
	@bash -c 'echo -ne "\r[$(GREEN)$(BOLD)$(PERCENT)%] Compiling Printf..."'
endef

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
		@echo
		@ar rcs $(NAME) $(OBJ)
		@echo "$(CYAN)$(BOLD)Printf Created Succefully √$(RESET)"
		@ranlib $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(update_progress)
	@$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
