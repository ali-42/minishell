/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:12:10 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/31 04:53:31 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_key(char *s)
{
	int		i;
	char	*key;

	i = 0;
	while (s[i] != '=' && s[i] != '+')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (key == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '=' && s[i] != '+')
	{
		key[i] = s[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static char	*get_new_value(char *s)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (s[i] != '=')
		i++;
	while (s[j] != '\0')
		j++;
	if (j - (i + 1) == 0)
		return (NULL);
	value = (char *)malloc(sizeof(char) * (j - i + 1));
	if (value == NULL)
		return (NULL);
	i++;
	j = 0;
	while (s[i] != '\0')
	{
		value[j] = s[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

static char	*get_value(char *s, char *key, t_env *env)
{
	char	*value1;
	char	*value2;
	char	*value3;

	value1 = get_env(key, env);
	if (is_export_add(s) == 1 && value1 != NULL)
	{
		value2 = get_new_value(s);
		value3 = ft_strjoin(value1, value2);
		free(value2);
		return (value3);
	}
	else
		return (get_new_value(s));
}

int	ft_export_arg(char **arg, t_env **env)
{
	int		i;
	int		ret;
	char	*key;
	char	*value;

	i = 1;
	ret = 0;
	while (arg[i] != NULL)
	{
		if (check_invalid_export(arg[i]) == 1)
			ret = 1;
		else if (check_equal(arg[i]) != 0)
		{
			key = get_key(arg[i]);
			value = get_value(arg[i], key, *env);
			if (is_in_env(key, *env) == 0)
				add_to_env(key, value, env);
			else
				set_env(key, value, *env);
			free(key);
			free(value);
		}
		i++;
	}
	return (ret);
}
