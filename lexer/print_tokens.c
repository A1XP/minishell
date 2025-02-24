/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:09:55 by natallia          #+#    #+#             */
/*   Updated: 2025/02/04 12:39:36 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <stdio.h>

const char *type[] = {
	"NEWLINE",
	"SEMICOLON",
	"PAREN_OPEN",
	"PAREN_CLOSE",
	"AND",
	"OR",
	"PIPE",
	"WORD",
	"REDIR_IN",
	"REDIR_OUT",
	"APPEND",
	"HEREDOC",
	"VARIABLE",
	"ASSIGN",
	"STR_DOUBLE_Q",
	"STR_SINGLE_Q",
	"SPACE",
	"COMMENT"
};

void	print_tokens(t_token *tokens)
{
	printf("TOKENS:\n");
	while (tokens)
	{
		printf("Token: %12s: \"%s\"\n", type[tokens->type], tokens->value);
		tokens = tokens->next;
	}
}
