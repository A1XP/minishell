/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:25:19 by nkhamich          #+#    #+#             */
/*   Updated: 2025/02/09 12:30:23 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*big_string;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	big_string = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (big_string == NULL)
		return (NULL);
	ft_memcpy(big_string, s1, s1_len);
	ft_memcpy(big_string + s1_len, s2, s2_len);
	big_string[s1_len + s2_len] = '\0';
	free(s1);
	return (big_string);
}
