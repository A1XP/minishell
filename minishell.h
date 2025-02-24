/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:37:23 by natallia          #+#    #+#             */
/*   Updated: 2025/02/18 16:09:44 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "execution/execution.h"
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_mshell_phase
{
	MINISHELL_READLINE,
	MINISHELL_LEXER,
	MINISHELL_PARSER,
	MINISHELL_EXECUTER,
	MINISHELL_CLEANUP,
	MINISHELL_EXIT
}	t_mshell_phase;

typedef struct s_mshell
{
	char		*input;
	char		**envp_copy;
	t_token		*tokens;
	t_ast_node	*ast;
	char		*prompt;
	t_executer  exec;
}	t_mshell;

t_mshell_phase	mshell_start(t_mshell *mshell, char **envp);
t_mshell_phase	mshell_readline(t_mshell *mshell);
t_mshell_phase	mshell_lexer(t_mshell *mshell);
t_mshell_phase	mshell_parser(t_mshell *mshell);
t_mshell_phase	mshell_cleanup(t_mshell *mshell);
t_mshell_phase	mshell_execution(t_mshell *mshell);

// utils
char			**get_envp_copy(char **envp);
void			free_envp_copy(char **envp_copy);
void			free_tokens(t_token **tokens);

#endif
