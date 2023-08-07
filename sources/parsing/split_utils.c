/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:34:15 by ali               #+#    #+#             */
/*   Updated: 2022/01/31 08:52:04 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_pass_sep(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	if (str[i] == '<' && str[i + 1] == '<')
		return (2);
	return (1);
}

int	ft_next_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	ft_pass_quote(char *str)
{
	int		i;
	char	c;

	if (!ft_quote_closed(str))
		return (ft_pass_word(str));
	i = 0;
	c = str[i];
	i++;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (i);
	return (i + 1);
}

int	ft_pass_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (ft_is_separator(str[i]))
		return (i + ft_pass_sep(&str[i]));
	if ((str[i] == '\'' || str[i] == '\"') && ft_quote_closed(&str[i]))
		return (i + ft_pass_quote_word(&str[i]));
	while (str[i] && str[i] != ' ' && !ft_is_separator(str[i]))
	{
		if ((str[i] == '\'' || str[i] == '\"') && ft_quote_closed(&str[i]))
			i += ft_pass_quote_word(&str[i]);
		if (str[i] && str[i] != ' ' && !ft_is_separator(str[i]))
			i++;
	}
	return (i);
}
