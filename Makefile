# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 14:57:58 by thblack-          #+#    #+#              #
#    Updated: 2025/11/10 12:31:14 by thblack-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PROJECT NAME
PROJECT		= minishell
NAME		= minishell

# PROJECT DIRECTORIES
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= inc
PARSER_DIR	= src/parser
ULTILS_DIR	= src/utils

# PROJECT SOURCES: Explicitly states
SRC_FILES	= main.c
SRC_DEV		= $(shell find src -name "*.c")
SRC			= $(SRC_DEV)
# SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# PROJECT HEADER
HEADER		= $(INC_DIR)/minishell.h

# PROJECT OBJECTS
OBJ			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_DIRS	= $(sort $(dir $(OBJ)))
DEPS		= $(OBJ:.o=.d)

# TOOLS
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CGENERAL	= -O2
CFAST		= -O3
CDEBUG		= -g -O0
MAKE_QUIET	= --no-print-directory
MAKE_LIB	= make -C

# REMOVE
RMFILE = rm -f
RMDIR = rm -rf

# MAKE DIRECTORY
MKDIR		= mkdir -p

# LIBFT LINKING
LIBFT_DIR	= ./libft
LIBFT_H		= $(LIBFT_DIR)/libft.h
LIBFT_A		= $(LIBFT_DIR)/libft.a

# INCLUDE PATHS AND LIBRARIES
INC			= -I. -I$(LIBFT_DIR) -I$(INC_DIR)
LIBFT		= -L$(LIBFT_DIR) -lft
READLINE	= -lreadline -lncurses
LIBS		= $(LIBFT) $(READLINE)

# MESSAGES
START		= @echo "==== THOMASROFF MAKEFILE =============" \
			  && echo "==== STARTED: $(shell date '+%Y-%m-%d %H:%M:%S') ===="
BUILD_PROJ	= @echo "==== BUILDING $(PROJECT) =============="
BUILD_LIBFT	= @echo "==== BUILDING LIBFT =================="
COMPILED	= @echo "$(PROJECT) compiled successfully"
FINISH		= @echo "==== BUILD COMPLETE ==================" \
			  && echo "==== FINISHED: $(shell date '+%Y-%m-%d %H:%M:%S') ==="
SPACER		= @echo ""

# <<<<<<< MAIN TARGETS >>>>>>>

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(START)
	$(BUILD_PROJ)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBS) -o $(NAME)
	$(COMPILED)
	$(FINISH)

$(LIBFT_A):
	@$(MAKE_LIB) $(LIBFT_DIR) $(MAKE_QUIET)
	$(SPACER)

# $(OBJ_DIR):
#	@$(MKDIR) $(OBJ_DIR)

$(OBJ_DIRS):
	@$(MKDIR) $@

 $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIRS)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

-include $(DEPS)

.SECONDARY: $(OBJ) 

# <<<<<<< PHONY TARGETS >>>>>>>

clean:
	@echo "Removing object files"
	@$(RMDIR) $(OBJ_DIR)
	@$(MAKE_LIB) libft clean $(MAKE_QUIET)

fclean:
	@echo "Removing object files"
	@$(RMDIR) $(OBJ_DIR)
	@echo "Removing static library files"
	@$(RMFILE) $(NAME)
	@$(MAKE_LIB) libft fclean $(MAKE_QUIET)

re: fclean all

run: $(NAME)
	@echo "Running $(NAME)..."
	@./$(NAME)

retry: clean all run

.PHONY: all clean fclean re debug
