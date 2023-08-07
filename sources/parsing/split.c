/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:38:19 by ali               #+#    #+#             */
/*   Updated: 2022/02/02 09:56:07 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_words_line(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		words += ft_next_word(&str[i]);
		i += ft_pass_word(&str[i]);
	}
	return (words);
}

int	ft_wordlen_line(char *str)
{
	int	i;

	i = 0;
	if (ft_is_separator(str[i]))
		return (ft_pass_sep(str));
	if (str[i] == '\'' || str[i] == '\"')
		return (ft_pass_quote_word(str));
	while (str[i] && str[i] != ' ' && !ft_is_separator(str[i]))
	{
		if ((str[i] == '\'' || str[i] == '\"') && ft_quote_closed(&str[i]))
			i += ft_pass_quote_word(&str[i]);
		if (str[i] && str[i] != ' ' && !ft_is_separator(str[i]))
			i++;
	}
	return (i);
}

char	*ft_copy_word(char *str)
{
	char	*word;
	int		size;
	int		i;

	if (!str)
		return (NULL);
	size = ft_wordlen_line(str);
	word = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	ft_fill(char **strs, char *str, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		strs[i] = ft_copy_word(&str[j]);
		j += ft_pass_word(&str[j]);
		while (str[j] == ' ')
			j++;
		i++;
	}
	strs[i] = NULL;
}

char	**ft_splitline(char *str)
{
	char	**strs;
	int		size;

	if (!str)
	{
		strs = malloc(sizeof(char *));
		if (!strs)
			return (NULL);
		strs[0] = NULL;
		return (strs);
	}
	while (*str && *str == ' ')
		str++;
	size = ft_count_words_line(str);
	strs = malloc(sizeof(char *) * (size + 1));
	if (!strs)
		return (NULL);
	ft_fill(strs, str, size);
	return (strs);
}
