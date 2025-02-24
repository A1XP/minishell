/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:31:26 by natallia          #+#    #+#             */
/*   Updated: 2025/02/04 13:24:45 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	get_space_len(const char *str)
{
	int	len;

	len = 0;
	while (ft_isspace(str[len]))
		len++;
	return (len);
}

static void	copy_space(const char **input, char *temp)
{
	int		idx;

	idx = 0;
	while (ft_isspace(**input))
	{
		temp[idx] = **input;
		idx++;
		(*input)++;
	}
	temp[idx] = '\0';
}

int	handle_spaces(const char **input, t_token **tokens)
{
	int			len;
	char		*temp;
	t_token		*new_token;

	len = get_space_len(*input);
	temp = malloc((len + 1) * sizeof(char));
	if (temp == NULL)
		return (LEXER_CRITICAL_ERROR);
	copy_space(input, temp);
	new_token = create_token(SPACE, temp);
	free(temp);
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	return (LEXER_DEFAULT);
}
