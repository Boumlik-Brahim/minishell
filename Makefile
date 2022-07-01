NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror \

READLFLAGS = -L $(shell brew --prefix readline)/lib -lreadline \
    -L $(shell brew --prefix readline)/lib -lhistory \
    -I $(shell brew --prefix readline)/include

LIBFT = -L libft -lft

HEADER = minishell.h

# execution part

BUILTINS =  env export export-utils unset echo cd pwd exit

EXEC = minishell_errors minishell_free minishell_utis execute nonbuiltins pipes redirections signals

# parsing part -fsanitize=address -static-libsan -I ./ -I libft/ 

LEXER = lexer tokenizer get_operators get_operators_util get_word get_word_util check_errors check_qoutes

PARSER = parser process_data get_cmd get_operators

TOOLS = tokennew tokenadd_front tokenadd_back tokensize tokenlast tokendelone shell_new shell_last shell_size shelladd_back shelladd_front

ENV = get_env

MAIN = minishell

SRC = $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/lexer/, $(LEXER))) \
	  $(addsuffix .c, $(addprefix srcs/parser/, $(PARSER))) \
	  $(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \
	  $(addsuffix .c, $(addprefix srcs/executor/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/executor/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make bonus -sC libft/
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(READLFLAGS) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -g
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC}  -I $(shell brew --prefix readline)/include ${CFLAGS} -c $< -o $@

.INTERMEDIATE: $(OBJ)

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -sC libft/
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -sC libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: all
	./minishell

norm:
	@norminette $(SRC) 
	@norminette $(HEADER)

.PHONY: clean fclean re test norm