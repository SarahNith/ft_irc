NAME = ircserv

CXX = c++
MAKE = make
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
CMDS_DIR = $(SRC_DIR)cmds/
CMDEXEC_DIR = $(SRC_DIR)cmds/cmdExec/
CLASSES_DIR = $(SRC_DIR)classes/

SRC_FILES = main.cpp parsing.cpp

CLASSES_FILES = channel.cpp client.cpp server.cpp

CMDEXEC_FILES = cmdExec.cpp sendMsg.cpp

CMD_FILES = join.cpp nick.cpp pass.cpp privmsg.cpp user.cpp


#SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o)) \
	  $(addprefix $(OBJ_DIR), $(CLASSES_FILES:.cpp=.o)) \
	  $(addprefix $(OBJ_DIR), $(CMD_FILES:.cpp=.o)) \
	  $(addprefix $(OBJ_DIR), $(CMDEXEC_FILES:.cpp=.o))



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
# 	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
# 	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@echo -e "$(GREEN)$(NAME) compiled!$(DEFAULT)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@echo -e "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)%.o: $(CLASSES_DIR)%.cpp | $(OBJ_DIR)
	@echo -e "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)%.o: $(CMDS_DIR)%.cpp | $(OBJ_DIR)
	@echo -e "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)%.o: $(CMDEXEC_DIR)%.cpp | $(OBJ_DIR)
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