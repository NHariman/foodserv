# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mjiam <mjiam@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/28 20:58:28 by mjiam         #+#    #+#                  #
#    Updated: 2022/10/18 21:12:59 by mjiam         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		:=	webserv

CC			:= 	clang++

FLAGS		= 	-Wall -Wextra -Werror -std=c++11 -I$(SRC_DIR)

ifdef DEBUG
FLAGS		+=	-fsanitize=address -fno-omit-frame-pointer -g
endif

SRC			=	main.cpp $(SRC_CONF) $(SRC_CONN) $(SRC_REQ) $(SRC_RESOLVE) \
				$(SRC_RESP) $(SRC_UTILS) $(SRC_ERR) $(SRC_CGI) $(SRC_SERV)

SRC_CGI		=	$(addprefix $(SRC_DIR)/$(CGI_DIR)/, cgi_argv_envp.cpp \
													cgi_file_validation.cpp \
													cgi_handler.cpp \
													cgi_parent_child.cpp \
													cgi_pathfinder.cpp \
													cgi.cpp)

SRC_CONF	=	$(addprefix $(SRC_DIR)/$(CONF_DIR)/, config_interface.cpp \
														listen.cpp \
														location_context_setters.cpp \
														location_context_verification.cpp \
														location_context.cpp \
														nginx_config_file_handler.cpp \
														nginx_config_get_servers.cpp \
														nginx_config.cpp \
														server_context_setters.cpp \
														server_context_verification.cpp \
														server_context.cpp \
														server_name.cpp \
														setup.cpp \
					$(addprefix directive_validation/, allowed_methods.cpp \
														autoindex.cpp \
														cgi_pass.cpp \
														cgi_pass_parser.cpp \
														client_max_body_size.cpp \
														index.cpp \
														location_uri.cpp \
														return_dir.cpp\
														root.cpp))

SRC_CONN	=	$(addprefix $(SRC_DIR)/$(CONN_DIR)/, connection.cpp)

SRC_ERR		=	$(addprefix $(SRC_DIR)/$(ERR_DIR)/, error_responses.cpp)
													
SRC_REQ		=	$(addprefix $(SRC_DIR)/$(REQ_DIR)/, request.cpp \
													request_validator.cpp \
													uri.cpp \
							$(addprefix parser/,	request_parser.cpp \
													request_target_parser.cpp \
													header_field_parser.cpp \
													request_line_parser.cpp \
													uri_host_parser.cpp \
													chunked_parser.cpp))

SRC_RESOLVE	=	$(addprefix $(SRC_DIR)/$(TAR_DIR)/, location_selection.cpp \
														server_selection.cpp \
														resolved_path.cpp \
														target_config.cpp)

SRC_RESP	=	$(addprefix $(SRC_DIR)/$(RESP_DIR)/, file_handler.cpp \
														response_generator.cpp \
														response_handler.cpp \
														response.cpp)

SRC_SERV	=	$(addprefix $(SRC_DIR)/$(SERV_DIR)/, kernel_events.cpp socket.cpp)

SRC_UTILS	=	$(addprefix $(SRC_DIR)/$(UTILS_DIR)/, cgi_utils.cpp \
														config_utils.cpp \
														file_handling.cpp \
														error.cpp \
														is_functions.cpp \
														mime_types.cpp \
														status_codes.cpp \
														request_utils.cpp \
														timer.cpp)

OBJ			= 	$(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

# DIRECTORIES
SRC_DIR		=	src
CGI_DIR		=	cgi
CONF_DIR	=	config
CONN_DIR	=	connection
ERR_DIR		=	err
REQ_DIR		=	request
TAR_DIR		=	resolved_target
RESP_DIR	=	response
SERV_DIR	=	server
UTILS_DIR	=	utils
TEST_DIR	=	google_test
OBJ_DIR		=	obj

# COLORS
CYAN		= 	\033[0;36m
PURPLE		= 	\033[0;35m
BLUE		= 	\033[0;34m
YELLOW		=	\033[0;33m
GREEN		= 	\033[0;32m
RESET		= 	\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $@
	@echo "Executable $(CYAN)$@$(RESET) made"

# compiles and runs each google test suite
test: all
	@echo "$(YELLOW)Running all unit tests\n$(RESET)"
	@for test in $(TEST_DIR)/*; do cd $$test && ./gotest.sh && cd ../.. || exit 1; done

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "$(PURPLE)Compiling: $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

debug: $(OBJ)
	@echo "$(GREEN)Debug mode: compiling with address sanitizer$(RESET)"
	@$(MAKE) DEBUG=1

clean:
	@echo "$(BLUE)Cleaning$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Removed: $(OBJ_DIR) folder$(RESET)"

quietclean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(BLUE)Removing: $(NAME)$(RESET)"
	@rm -rf $(NAME)
	@echo "$(BLUE)Clean af$(RESET)"

re:
	@echo "$(BLUE)Once more from the top$(RESET)"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all run debug clean fclean re compare