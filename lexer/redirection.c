/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:55:22 by natallia          #+#    #+#             */
/*   Updated: 2025/02/10 14:02:21 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_redirection(const char **input, t_token **tokens)
{
	t_token		*new_token;

	if (ft_strncmp(*input, ">>", 2) == 0)
		new_token = create_token(APPEND, ">>");
	else if (ft_strncmp(*input, "<<", 2) == 0)
		new_token = create_token(HEREDOC, "<<");
	else if (**input == '>')
		new_token = create_token(REDIR_OUT, ">");
	else
		new_token = create_token(REDIR_IN, "<");
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	*input += ft_strlen(new_token->value);
	return (LEXER_DEFAULT);
}
