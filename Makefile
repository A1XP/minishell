# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 13:03:26 by nkhamich          #+#    #+#              #
#    Updated: 2025/03/07 12:54:02 by pkhvorov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
SRC			= lexer/and.c lexer/comment.c mshell_lexer.c \
			lexer/newline.c lexer/parentheses.c lexer/pipe_or.c \
			lexer/quote.c lexer/redirection.c lexer/token_utils.c \
			lexer/variable.c lexer/whitespace.c lexer/word.c \
			lexer/semicolon.c lexer/print_tokens.c lexer/tokenize_input.c \
			mshell_parser.c parser/assignment.c parser/ast_free.c \
			parser/ast_utils.c parser/build_ast.c parser/command.c parser/parentheses.c \
			parser/parse_input.c parser/print_tree.c parser/argument.c parser/group.c \
			parser/redirection.c mshell_main.c mshell_utils.c mshell_readline.c mshell_start.c \
			mshell_cleanup.c mshell_execution.c \
			execution/ft_builtin_pwd.c execution/ft_builtin_env.c  execution/ft_builtin_echo.c \
		  	execution/ft_execution.c execution/exec_utils.c execution/common_utils.c execution/env_utils.c \
		  	execution/ft_builtin_cd.c execution/ft_builtin_export.c execution/ft_builtin_unset.c \
			execution/ft_exec_pipe.c execution/ft_builtin_exit.c execution/ft_redirection.c \
			execution/ft_redirection_heredoc.c execution/ft_redirection_group.c signals/signals.c
OBJ_DIR		= obj
OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS	= $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

LIBS = -lreadline

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Object directory created for $(NAME)."

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "$(NAME) executable created successfully."

$(LIBFT):
	@make -C $(LIBFT_PATH) all

bonus: all

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files cleaned for $(NAME)."

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -rf $(NAME)
	@echo "Executable fully cleaned."

re: fclean all

.PHONY: all bonus clean fclean re libft
