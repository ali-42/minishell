/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:27:15 by ali               #+#    #+#             */
/*   Updated: 2022/01/31 12:31:50 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_key(char *envp)
{
	int		i;
	char	*key;

	i = 0;
	while (envp[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (envp[i] != '=')
	{
		key[i] = envp[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*ft_get_value(char *envp)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (envp[i] != '=')
		i++;
	i++;
	value = malloc(sizeof(char) * (ft_strlen(envp) + 1));
	if (!value)
		return (NULL);
	j = 0;
	while (envp[i + j])
	{
		value[j] = envp[i + j];
		j++;
	}
	value[j] = '\0';
	return (value);
}

t_env	*ft_parse_env(char **envp)
{
	t_env	*env;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	i = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[i])
	{
		key = ft_get_key(envp[i]);
		value = ft_get_value(envp[i]);
		add_to_env(key, value, &env);
		free(key);
		free(value);
		if (env == NULL)
			return (NULL);
		i++;
	}
	return (env);
}
