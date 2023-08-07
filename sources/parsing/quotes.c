/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:55:05 by ali               #+#    #+#             */
/*   Updated: 2022/02/02 17:57:12 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote_closed(char *str)
{
	int		i;
	char	c;

	c = str[0];
	i = 1;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (0);
	return (1);
}

void	ft_fill_unquote(char *sub, char *str, int index, char c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < index)
		sub[i] = str[i];
	j = i;
	while (str[i] != c)
	{
		sub[j] = str[i];
		ft_increment(&i, &j);
	}
	i++;
	while (str[i] != c)
	{
		sub[j] = str[i];
		ft_increment(&i, &j);
	}
	i++;
	while (str[i])
	{
		sub[j] = str[i];
		ft_increment(&i, &j);
	}
	sub[j] = '\0';
}

int	ft_size_unquote(char *str, int index, int c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < index)
		ft_increment(&i, &size);
	while (str[i] != c)
		ft_increment(&i, &size);
	i++;
	while (str[i] != c)
		ft_increment(&i, &size);
	i++;
	while (str[i])
		ft_increment(&i, &size);
	return (size);
}

char	*ft_remove_quote(char *str, int index)
{
	char	c;
	char	*sub;
	int		i;
	int		size;

	i = index;
	if (!str[i])
		return (str);
	while (str[i] && str[i] != '\'' && str[i] != '\"')
		i++;
	if (!str[i])
		return (str);
	if (!ft_quote_closed(&str[i]))
		return (str);
	c = str[i];
	while (str[i + 1] && str[i + 1] != c)
		i++;
	size = ft_size_unquote(str, index, c);
	sub = malloc(sizeof(char) * (size + 1));
	if (!sub)
		return (NULL);
	ft_fill_unquote(sub, str, index, c);
	free(str);
	return (ft_remove_quote(sub, i));
}

void	ft_quotes(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (ft_has_no_quotes(strs[i]))
			strs[i] = ft_no_spaces(strs[i]);
		else if (strs[i][0] && !ft_is_separator(strs[i][1]))
			strs[i] = ft_remove_quote(strs[i], 0);
		i++;
	}
}
