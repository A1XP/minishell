/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:03:54 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/05 16:34:56 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			if (array[i] != NULL)
			{
				free_ptr(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	print_darray(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}
