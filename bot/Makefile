NAME = ircBot

CXX = c++
MAKE = make
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
INC_DIR = ./includes/

SRC_FILES = main.cpp botServer.cpp bot.cpp

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))

INCLUDES = -I $(INC_DIR)

DEFAULT = \033[0m
DEF_COLOR = \033[0;90m
WHITE = \033[1;37m
GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
MAGENTA = \033[0;95m

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@echo -e "$(GREEN)$(NAME) compiled!$(DEFAULT)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@echo -e "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "$(MAGENTA)$(NAME) object directory cleaned!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo -e "$(CYAN)$(NAME) executables and objects removed succesfully!$(DEFAULT)"

re: clean fclean all

.PHONY: all clean fclean re