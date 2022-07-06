Color_Off='\033[0m'       # Text Reset
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow


define BANNER

	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     
	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     
	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     
	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     
	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
                                                                                                     
endef
export BANNER


NAME = minishell

CC = cc

CFLAGS = -fsanitize=address -static-libsan -I ./ -I libft/ \
		-Wall -Wextra -Werror \

MAIN = minishell

RFLAGS =  -L$(shell brew --prefix readline)/lib -lreadline \
 		-L$(shell brew --prefix readline)/lib -lhistory \
 		-I$(shell brew --prefix readline)/include 

LIBFT = -L libft -lft

HEADER = minishell.h


#-------------------------------------------------------------------------------
# execution part
BUILTINS =  env export export_print export_utils unset echo cd pwd exit

EXEC = minishell_errors minishell_free minishell_utis execute backbone heredoc signals

ENV = get_env get_env_util

#-------------------------------------------------------------------------------
# parsing part

LEXER = lexer tokenizer get_operators get_operators_util get_word \
	get_word_util check_errors check_qoutes

PARSER = parser process_data get_cmd get_cmd_util get_operators

TOOLS = tokennew tokenadd_front tokenadd_back tokensize tokenlast \
	tokendelone token_clear shell_new shell_last shell_size shelladd_back \
	shelladd_front shelldelone shell_clear

#-------------------------------------------------------------------------------

SRC = $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/lexer/, $(LEXER))) \
	  $(addsuffix .c, $(addprefix srcs/parser/, $(PARSER))) \
	  $(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \
	  $(addsuffix .c, $(addprefix srcs/executor/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/executor/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \

OBJ = $(SRC:c=o)

all: banner $(NAME)

banner:
	@clear
	@echo "\n"
	@echo $(BGreen)"$$BANNER"$(Color_Off)
	@echo $(BYellow)"                     made by Hssain Aitkadir & Boumlik Brahim\n"$(Color_Off)

$(NAME): $(OBJ)
	@echo "\n"
	@make bonus -sC libft/
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) -lreadline $(CFLAGS) $(RFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\n\033[0mDone !"

%.o: %.c $(HEADER)
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} -I $(shell brew --prefix readline)/include ${CFLAGS}  -c $< -o $@

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