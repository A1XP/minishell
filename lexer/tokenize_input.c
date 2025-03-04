/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:48:49 by nkhamich          #+#    #+#             */
/*   Updated: 2025/03/03 12:58:34 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	handle_other_chars(const char **input, t_token **tokens)
{
	if (**input == '#')
		return (handle_comment(input, tokens));
	else if (**input == '$')
		return (handle_dollar(input, tokens));
	else
		return (handle_semicolon(input, tokens));
}

void	tokenize_input(const char *input, t_token **tokens, int *status)
{
	while (*input && *status == LEXER_DEFAULT)
	{
		if (*input == '|')
			*status = handle_pipe_or(&input, tokens);
		else if (*input == '&')
			*status = handle_and(&input, tokens);
		else if (*input == '(' || *input == ')')
			*status = handle_parentheses(&input, tokens);
		else if (*input == '>' || *input == '<')
			*status = handle_redirection(&input, tokens);
		else if (*input == '\'' || *input == '\"')
			*status = handle_quotes(&input, tokens);
		else if (*input == '\n')
			*status = handle_newline(&input, tokens);
		else if (ft_strchr("#$;", *input))
			*status = handle_other_chars(&input, tokens);
		else if (*input == ' ')
			*status = handle_spaces(&input, tokens);
		else
			*status = handle_word(&input, tokens);
	}
}
