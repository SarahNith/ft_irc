NAME = ircserv

CC = c++
MAKE = make
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_DIR = srcs/
OBJ_DIR = obj/
INC_DIR = includes/

SRC_FILES = main.cpp \
			/classes/channel.cpp classes/client.cpp classes/server.cpp


SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = 	$(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))



INCLUDES = -I $(INC_DIR)

DEFAULT = \033[0m
DEF_COLOR = \033[0;90m
WHITE = \033[1;37m
GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
MAGENTA = \033[0;95m

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@echo -e "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) compiled!$(DEFAULT)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@echo -e "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<


clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "$(MAGENTA)$(NAME) object directory cleaned!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo -e "$(CYAN)$(NAME) executables and objects removed succesfully!$(DEFAULT)"

re: fclean clean all

.PHONY: all clean fclean re