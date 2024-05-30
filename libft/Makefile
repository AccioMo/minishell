CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = libft.a
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = libft.h
FILES = ft_calloc.c ft_isdigit.c ft_memset.c ft_split.c ft_strlcat.c ft_strnstr.c ft_toupper.c ft_isprint.c \
		ft_memchr.c ft_putchar_fd.c ft_strchr.c ft_strlcpy.c ft_strrchr.c ft_isalnum.c ft_itoa.c ft_memcmp.c \
		ft_putendl_fd.c ft_strdup.c ft_strlen.c ft_strtrim.c ft_atoi.c ft_isalpha.c ft_memcpy.c ft_putnbr_fd.c \
		ft_striteri.c ft_strmapi.c ft_substr.c ft_bzero.c ft_isascii.c ft_memmove.c ft_putstr_fd.c ft_strjoin.c \
		ft_strncmp.c ft_tolower.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c \
		ft_lstiter_bonus.c ft_lstadd_back_bonus.c ft_lstmap_bonus.c ft_lstadd_front_bonus.c ft_lstnew_bonus.c
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
	@bash -c 'echo -ne "\r[$(GREEN)$(BOLD)$(PERCENT)%] Compiling Libft..."'
endef

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "\n$(CYAN)$(BOLD)Libft Created Succefully √$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(update_progress)
	@$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
