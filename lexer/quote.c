/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:09:54 by natallia          #+#    #+#             */
/*   Updated: 2025/02/17 13:53:50 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	quoted_len(const char *str, char quote, bool *is_closed)
{
	int		len;

	len = 0;
	while (str[len] != quote && str[len] != '\0')
		len++;
	if (str[len] != quote)
		*is_closed = false;
	return (len);
}

static void	copy_quoted_str(const char **input, char *temp, char quote)
{
	int		idx;

	idx = 0;
	while (**input != quote && **input != '\0')
	{
		// if (str[*i] == '$')
		// 	expand_variable(&str[*i], temp, &idx, i);
		temp[idx] = **input;
		idx++;
		(*input)++;
	}
	temp[idx] = '\0';
	(*input)++;
}

static int	double_quotes(const char **input, t_token **tokens)
{
	int			len;
	bool		is_closed;
	char		*temp;
	t_token		*new_token;

	(*input)++;
	is_closed = true;
	len = quoted_len(*input, '\"', &is_closed);
	if (is_closed == false)
		return (LEXER_ERROR);
	temp = malloc((len + 1) * sizeof(char));
	if (temp == NULL)
		return (LEXER_CRITICAL_ERROR);
	copy_quoted_str(input, temp, '\"');
	new_token = create_token(STR_DOUBLE_Q, temp);
	free(temp);
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	return (LEXER_DEFAULT);
}

static int	single_quotes(const char **input, t_token **tokens)
{
	int			len;
	bool		is_closed;
	char		*temp;
	t_token		*new_token;

	(*input)++;
	is_closed = true;
	len = quoted_len(*input, '\'', &is_closed);
	if (is_closed == false)
		return (LEXER_ERROR);
	temp = malloc((len + 1) * sizeof(char));
	if (temp == NULL)
		return (LEXER_CRITICAL_ERROR);
	copy_quoted_str(input, temp, '\'');
	new_token = create_token(STR_SINGLE_Q, temp);
	free(temp);
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	return (LEXER_DEFAULT);
}

int	handle_quotes(const char **input, t_token **tokens)
{
	int		status;

	status = LEXER_DEFAULT;
	if (**input == '\'')
	{
		status = single_quotes(input, tokens);
		if (status == LEXER_ERROR)
			ft_putendl_fd("minishell: unclosed single quote", 2);
	}
	else
	{
		status = double_quotes(input, tokens);
		if (status == LEXER_ERROR)
			ft_putendl_fd("minishell: unclosed double quote", 2);
	}
	return (status);
}
