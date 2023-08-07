/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:41:41 by ali               #+#    #+#             */
/*   Updated: 2022/01/31 09:15:18 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmp_key(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_fill_joinenv(char *joined, char *key, char *value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (key[i])
	{
		joined[j] = key[i];
		i++;
		j++;
	}
	joined[j] = '=';
	j++;
	joined[j] = '\"';
	j++;
	i = 0;
	while (value[i])
	{
		joined[j] = value[i];
		i++;
		j++;
	}
	joined[j] = '\"';
	j++;
	joined[j] = '\0';
}

char	*ft_strjoinenv(t_env *env)
{
	char	*joined;

	joined = malloc(sizeof(char) *(ft_strlen(env->key)
				+ ft_strlen(env->value) + 4));
	if (!joined)
		return (NULL);
	ft_fill_joinenv(joined, env->key, env->value);
	return (joined);
}

void	ft_sort_env_export(char **strs)
{
	int		i;
	int		j;
	char	*tmp;
	int		size;

	i = 0;
	j = 0;
	while (strs[i])
		i++;
	size = i;
	while (j < size)
	{
		i = 0;
		while (strs[i])
		{
			if (strs[i + 1] && ft_cmp_key(strs[i], strs[i + 1]) > 0)
			{
				tmp = strs[i];
				strs[i] = strs[i + 1];
				strs[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}
