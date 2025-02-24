/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:53:07 by natallia          #+#    #+#             */
/*   Updated: 2025/02/04 13:20:59 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	copy_comment(const char **str, char *temp)
{
	int		idx;

	idx = 0;
	while (**str != '\n' && **str != '\0')
	{
		temp[idx] = **str;
		idx++;
		(*str)++;
	}
	temp[idx] = '\0';
}

static int	get_comment_len(const char *str)
{
	int		len;

	if (ft_strchr(str, '\n'))
		len = ft_strchr(str, '\n') - str;
	else
		len = ft_strlen(str);
	return (len);
}

int	handle_comment(const char **input, t_token **tokens)
{
	char		*temp;
	t_token		*new_token;

	(*input)++;
	temp = malloc((get_comment_len(*input) + 1) * sizeof(char));
	if (temp == NULL)
		return (LEXER_CRITICAL_ERROR);
	copy_comment(input, temp);
	new_token = create_token(COMMENT, temp);
	free(temp);
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	return (LEXER_DEFAULT);
}
