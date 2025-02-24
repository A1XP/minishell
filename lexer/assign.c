/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:56:05 by nkhamich          #+#    #+#             */
/*   Updated: 2025/02/04 12:49:58 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_assign(const char **input, t_token **tokens)
{
	t_token		*new_token;

	new_token = create_token(ASSIGN, "=");
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	(*input)++;
	return (LEXER_DEFAULT);
}
