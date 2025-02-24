/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:54:09 by natallia          #+#    #+#             */
/*   Updated: 2025/02/04 12:56:45 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_pipe_or(const char **input, t_token **tokens)
{
	t_token		*new_token;

	if (ft_strncmp(*input, "||", 2) == 0)
		new_token = create_token(OR, "||");
	else
		new_token = create_token(PIPE, "|");
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	*input += ft_strlen(new_token->value);
	return (LEXER_DEFAULT);
}
