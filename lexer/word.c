/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:51:06 by natallia          #+#    #+#             */
/*   Updated: 2025/03/03 12:54:52 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	get_world_len(const char *str)
{
	int		len;

	len = 0;
	while (str[len] && !ft_isspace(str[len]) && !ft_strchr(METACHAR, str[len]))
		len++;
	return (len);
}

static void	copy_word(const char **input, char *temp)
{
	int		idx;

	idx = 0;
	while (**input && !ft_isspace(**input) && !ft_strchr(METACHAR, **input))
	{
		temp[idx] = **input;
		idx++;
		(*input)++;
	}
	temp[idx] = '\0';
}

int	handle_word(const char **input, t_token **tokens)
{
	char		*temp;
	t_token		*new_token;

	temp = malloc((get_world_len(*input) + 1) * sizeof(char));
	if (temp == NULL)
		return (LEXER_CRITICAL_ERROR);
	copy_word(input, temp);
	new_token = create_token(WORD, temp);
	free(temp);
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	return (LEXER_DEFAULT);
}
