/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:03:48 by natallia          #+#    #+#             */
/*   Updated: 2025/02/04 13:01:06 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_semicolon(const char **input, t_token **tokens)
{
	t_token		*new_token;

	new_token = create_token(SEMICOLON, ";");
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	(*input)++;
	return (LEXER_DEFAULT);
}
