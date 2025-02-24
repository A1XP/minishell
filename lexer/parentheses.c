/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:29:04 by natallia          #+#    #+#             */
/*   Updated: 2025/02/04 13:21:17 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_parentheses(const char **input, t_token **tokens)
{
	t_token		*new_token;

	if (**input == '(')
		new_token = create_token(PAREN_OPEN, "(");
	else
		new_token = create_token(PAREN_CLOSE, ")");
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	(*input)++;
	return (LEXER_DEFAULT);
}
