/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:12:05 by natallia          #+#    #+#             */
/*   Updated: 2025/02/04 13:24:21 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	get_variable_len(const char *str)
{
	int		len;

	len = 0;
	if (!ft_isdigit(str[len]) && (ft_isalpha(str[len]) || str[len] == '_'))
		len++;
	while ((ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len + 1);
}

static void	copy_variable(const char **input, char *temp)
{
	int	idx;

	idx = 1;
	temp[0] = '$';
	if (!ft_isdigit(**input) && (ft_isalpha(**input) || **input == '_'))
	{
		temp[idx] = **input;
		idx++;
		(*input)++;
	}
	while ((ft_isalnum(**input) || **input == '_'))
	{
		temp[idx] = **input;
		idx++;
		(*input)++;
	}
	temp[idx] = '\0';
}

static int	exit_status_var(const char **input, t_token **tokens)
{
	t_token		*new_token;

	new_token = create_token(VARIABLE, "$?");
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	(*input)++;
	append_token(tokens, new_token);
	return (LEXER_DEFAULT);
}

static int	handle_var(const char **input, t_token **tokens)
{
	char		*temp;
	t_token		*new_token;

	(*input)++;
	if (**input == '?')
		return (exit_status_var(input, tokens));
	temp = malloc((get_variable_len(*input) + 1) * sizeof(char));
	if (temp == NULL)
		return (LEXER_CRITICAL_ERROR);
	copy_variable(input, temp);
	new_token = create_token(VARIABLE, temp);
	free(temp);
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	return (LEXER_DEFAULT);
}

int	handle_dollar(const char **input, t_token **tokens)
{
	t_token		*new_token;

	if (*input[1] == '\0'
		|| (!ft_isalpha(*input[1]) && !ft_strchr("_?", *input[1])))
	{
		new_token = create_token(WORD, "$");
		if (new_token == NULL)
			return (LEXER_CRITICAL_ERROR);
		append_token(tokens, new_token);
		(*input)++;
		return (LEXER_DEFAULT);
	}
	else
		return (handle_var(input, tokens));
}
