/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:09:33 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/16 17:55:30 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			words++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (words);
}

static int	ft_getword(char *s, char c, int n)
{
	int	i;
	int	word;

	i = 0;
	word = -1;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			word++;
			if (word == n)
				return (i);
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (0);
}

static int	ft_wordlen(char *s, char c, int n)
{
	int	i;
	int	len;

	i = ft_getword(s, c, n);
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*cpy;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		cpy = (char *)malloc(sizeof(char) * 1);
		if (cpy == NULL)
			return (NULL);
		cpy[0] = '\0';
		return (cpy);
	}
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (cpy == NULL)
		return (NULL);
	while (i < len)
		cpy[i++] = s[start + j++];
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		words;
	char	**tab;

	if (s == NULL)
		return (NULL);
	i = 0;
	words = ft_count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (tab == NULL)
		return (NULL);
	while (i < words)
	{
		tab[i] = ft_substr(s, ft_getword(s, c, i), ft_wordlen(s, c, i));
		if (tab[i] == NULL)
		{
			while (i > 0)
				free(tab[i--]);
			free(tab);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
