/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nospaces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 00:25:35 by ali               #+#    #+#             */
/*   Updated: 2022/01/25 00:42:07 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_no_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

int	ft_nospaces_size(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && size != 0)
			size++;
		while (str[i] && str[i] != ' ')
		{
			i++;
			size++;
		}
	}
	return (size);
}

void	ft_fill_nospaces(char *nospaces, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && j != 0)
		{
			nospaces[j] = ' ';
			j++;
		}
		while (str[i] && str[i] != ' ')
		{
			nospaces[j] = str[i];
			i++;
			j++;
		}
	}
	nospaces[j] = '\0';
}

char	*ft_no_spaces(char *str)
{
	char	*nospaces;

	nospaces = malloc(sizeof(char) * (ft_nospaces_size(str) + 1));
	if (!nospaces)
	{
		free(str);
		return (NULL);
	}
	ft_fill_nospaces(nospaces, str);
	free(str);
	return (nospaces);
}
