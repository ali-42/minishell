/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char2_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:20:06 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/26 18:46:37 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char2_size(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		i++;
	return (i);
}

char	**char2_dup(char **arg)
{
	int		i;
	int		size;
	char	**cpy;

	i = 0;
	size = char2_size(arg);
	cpy = malloc(sizeof(char *) * (size + 1));
	if (cpy == NULL)
		return (NULL);
	while (arg[i] != NULL)
	{
		cpy[i] = ft_strdup(arg[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
