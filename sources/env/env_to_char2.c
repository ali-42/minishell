/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_char2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:40:54 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/21 20:07:42 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_char2(t_env *env)
{
	int		i;
	char	**ret;

	if (env == NULL)
		return (NULL);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	while (env != NULL)
	{
		ret[i] = ft_strjoin3(env->key, "=", env->value);
		i++;
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}
