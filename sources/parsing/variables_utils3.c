/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:53:24 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 23:18:07 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_quotes(char c, int *indic)
{
	if (c == '\'' && indic[0] == 0 && indic[1] == 1)
		indic[0] = 1;
	else if (c == '\'' && indic[0] == 1 && indic[1] == 1)
		indic[0] = 0;
	if (c == '\"' && indic[1] == 1 && indic[0] == 0)
		indic[1] = 0;
	else if (c == '\"' && indic[1] == 0 && indic[0] == 0)
		indic[1] = 1;
}

int	size_new_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	i++;
	while (strs[i])
		i++;
	return (i);
}

void	ft_fill_newstrs(char **new, char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i])
	{
		new[j] = ft_strdup(strs[i]);
		i++;
		j++;
	}
	i++;
	while (strs[i])
	{
		new[j] = ft_strdup(strs[i]);
		i++;
		j++;
	}
	new[j] = NULL;
}

void	free_char2_null(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	i++;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**remove_empty(char	**strs, int null)
{
	char	**new;
	int		size;

	if (null == 0)
		return (strs);
	g_exit = 0;
	size = size_new_strs(strs);
	new = malloc(sizeof(char *) * size);
	if (!new)
	{
		free_char2_null(strs);
		return (NULL);
	}
	ft_fill_newstrs(new, strs);
	free_char2_null(strs);
	return (new);
}
