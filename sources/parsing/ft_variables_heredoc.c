/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:26:48 by ali               #+#    #+#             */
/*   Updated: 2022/01/28 15:45:00 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_quotes(char *str)
{
	char	*sub;
	int		i;
	int		j;

	sub = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!sub)
		return (NULL);
	i = 0;
	j = 0;
	sub[j] = '\'';
	j++;
	while (str[i])
	{
		sub[j] = str[i];
		i++;
		j++;
	}
	sub[j] = '\'';
	j++;
	sub[j] = '\0';
	free(str);
	return (sub);
}

char	*ft_joinall(char **strs, int num, int size)
{
	char	*joined;
	int		i;
	int		j;
	int		k;

	joined = malloc(sizeof(char) * (size + num + 1));
	if (!joined)
		return (NULL);
	i = -1;
	k = 0;
	while (strs[++i])
	{
		j = -1;
		while (strs[i][++j])
		{
			joined[k] = strs[i][j];
			k++;
		}
		if (strs[i])
			joined[k] = ' ';
		k++;
	}
	joined[k] = '\0';
	free_char2(strs);
	return (joined);
}

char	*ft_variables_heredoc(char *str)
{
	char	**strs;
	int		i;
	int		size;

	strs = ft_splitline(str);
	i = 0;
	size = 0;
	while (strs[i])
	{
		if (i > 0 && ft_strcmp(strs[i - 1], "<<") == 0)
		{
			strs[i] = ft_add_quotes(strs[i]);
			size += 2;
		}
		i++;
	}
	i = 0;
	while (strs[i])
	{
		size += ft_strlen(strs[i]);
		i++;
	}
	free(str);
	return (ft_joinall(strs, i, size));
}
