/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_noarg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:33:17 by ali               #+#    #+#             */
/*   Updated: 2022/01/31 09:14:37 by ali              ###   ########.fr       */
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

char	**env_to_char2_export(t_env *env)
{
	int		i;
	char	**ret;

	if (env == NULL)
		return (NULL);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	while (env != NULL)
	{
		ret[i] = ft_strjoinenv(env);
		i++;
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_export_noarg(t_env *env, int output)
{
	char	**strs;
	int		i;

	strs = env_to_char2_export(env);
	ft_sort_env_export(strs);
	i = 1;
	while (strs[i])
	{
		write(output, "declare -x ", 11);
		ft_putendl_fd(strs[i], output);
		i++;
	}
	free_char2(strs);
}

int	ft_export_redir(char **arg, t_env **env, int output)
{
	int		ret;

	ret = 0;
	if (!arg[1])
		ft_export_noarg(*env, output);
	else
		ret = ft_export_arg(arg, env);
	return (ret);
}
