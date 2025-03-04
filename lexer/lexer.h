/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:27:03 by natallia          #+#    #+#             */
/*   Updated: 2025/03/03 12:41:53 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "../libft/libft.h"

# define LEXER_DEFAULT 0
# define LEXER_ERROR 1
# define LEXER_CRITICAL_ERROR 2

# define METACHAR ";|$#<>\'\"()&"

typedef enum e_token_type
{
	NEWLINE,
	SEMICOLON,
	PAREN_OPEN,
	PAREN_CLOSE,
	AND,
	OR,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	VARIABLE,
	STR_DOUBLE_Q,
	STR_SINGLE_Q,
	SPACE,
	COMMENT
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

void	tokenize_input(const char *input, t_token **tokens, int *status);
int		handle_and(const char **input, t_token **tokens);
int		handle_comment(const char **input, t_token **tokens);
int		handle_newline(const char **input, t_token **tokens);
int		handle_parentheses(const char **input, t_token **tokens);
int		handle_pipe_or(const char **input, t_token **tokens);
int		handle_quotes(const char **input, t_token **tokens);
int		handle_redirection(const char **input, t_token **tokens);
int		handle_dollar(const char **input, t_token **tokens);
int		handle_semicolon(const char **input, t_token **tokens);
int		handle_spaces(const char **input, t_token **tokens);
int		handle_word(const char **input, t_token **tokens);

// token utils
void	append_token(t_token **token_lst, t_token *new);
t_token	*create_token(t_token_type type, const char *value);
t_token	*get_last_token(t_token *token_lst);

void	print_tokens(t_token *tokens);
#endif
