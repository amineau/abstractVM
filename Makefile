NAME = abstractVm
CC = g++ -std=c++11

SRCS = avm.cpp Factory.cpp Lexer.cpp Parser.cpp Error.cpp Manager.cpp

INCS = IOperand.hpp Operand.hpp Factory.hpp Lexer.hpp Parser.hpp Error.hpp Manager.hpp

SPATH = srcs
OPATH = objs
HPATH = includes

CFLAGS = -Wall -Werror -Wextra -g -I./$(HPATH)

INC = $(addprefix $(HPATH)/,$(INCS))
SRC = $(addprefix $(SPATH)/,$(SRCS))
OBJ = $(addprefix $(OPATH)/,$(SRCS:.cpp=.o))

WHITE   = \033[0m
DARK    = \033[1;30m
RED		= \033[1;31m
GREENB  = \033[1;32m
GREEN   = \033[0;32m
YELLOW  = \033[33m
CYAN    = \033[36m

all: $(OPATH) $(NAME) $(INC)

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) -o $@ $^ \
		&& printf "$(YELLOW)%-30s$(DARK)-->>\t$(GREEN)$@$(WHITE)\n" "Compilation"\
		|| (printf "$(YELLOW)%-30s$(DARK)-->>\t$(RED)$@$(WHITE)\n" "Compilation" \
		&& exit 1)

$(OPATH):
		@printf "$(YELLOW)%-30s$(WHITE)" "Creating $@ directory"
		@mkdir -p $(OPATH)
		@echo "$(GREENB)<<--$(WHITE)"

$(OPATH)/%.o: $(SPATH)/%.cpp
		@$(CC) $(CFLAGS) -o $@ -c $< \
		&& printf "%-30s$(DARK)-->>\t$(GREEN)$@$(WHITE)\n" "$<" \
		|| (printf "%-30s$(DARK)-->>\t$(RED)$@$(WHITE)\n" "$<" \
		&& exit 1)

clean:
		@printf "$(YELLOW)%-30s$(WHITE)" "Deleting $(OPATH)"
		@rm -rf $(OPATH)
		@echo "$(GREENB)<<--$(WHITE)"

fclean: clean
		@printf "$(YELLOW)%-30s$(WHITE)" "Deleting $(NAME)"
		@rm -f $(NAME)
		@echo "$(GREENB)<<--$(WHITE)"

re: fclean all
