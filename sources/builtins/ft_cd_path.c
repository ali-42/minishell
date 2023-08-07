/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 04:52:10 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/02 20:37:20 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path_exist(char *path)
{
	if (access(path, F_OK) == -1)
		return (1);
	if (access(path, X_OK) == -1)
		return (1);
	if (is_dir(path) == 0)
		return (1);
	return (0);
}

int	ft_cd_path(char *path, t_env **env)
{
	int		i;
	char	*path_to_test;
	char	**path_list;

	i = 0;
	if (get_env("CDPATH", *env) == NULL || path[0] == '/')
		return (ft_cd(path, env));
	path_list = ft_split(get_env("CDPATH", *env), ':');
	while (path_list[i] != NULL)
	{
		path_to_test = ft_strjoin3(path_list[i], "/", path);
		if (check_path_exist(path_to_test) == 0)
		{
			i = ft_cd(path_to_test, env);
			ft_putendl_fd(get_env("PWD", *env), 1);
			free_char2(path_list);
			free(path_to_test);
			return (i);
		}
		free(path_to_test);
		i++;
	}
	free_char2(path_list);
	return (ft_cd(path, env));
}
