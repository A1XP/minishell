/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:25:58 by natallia          #+#    #+#             */
/*   Updated: 2025/02/04 12:49:26 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_and(const char **input, t_token **tokens)
{
	t_token		*new_token;

	if (ft_strncmp(*input, "&&", 2) == 0)
		new_token = create_token(AND, "&&");
	else
		new_token = create_token(WORD, "&");
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	*input += ft_strlen(new_token->value);
	return (LEXER_DEFAULT);
}
