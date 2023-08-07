/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:26:23 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 18:09:01 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_variable(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$' && str[i + 1] && (str[i + 1] == '?' || str[i + 1] == '{'))
		return (1);
	if (str[i] == '$' && str[i + 1]
		&& !ft_is_vardel(str[i + 1], " ,.?/][}+=-*%$#@!\'\"\0"))
		return (1);
	return (0);
}

int	ft_is_vardel(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_has_quote(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	ft_fill_quote_value(char *str, char *sub, char c)
{
	int	i;
	int	j;

	if (c == '\'')
		sub[0] = '\"';
	else
		sub[0] = '\'';
	i = 0;
	j = 1;
	while (str[i])
	{
		sub[j] = str[i];
		i++;
		j++;
	}
	if (c == '\'')
		sub[j] = '\"';
	else
		sub[j] = '\'';
	j++;
	sub[j] = '\0';
}

char	*ft_quote_value(char *str)
{
	char	*sub;
	int		i;
	char	c;

	if (!str)
		return (NULL);
	sub = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!sub)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"')
		i++;
	if (!str[i])
		c = '\"';
	c = str[i];
	ft_fill_quote_value(str, sub, c);
	free(str);
	return (sub);
}
