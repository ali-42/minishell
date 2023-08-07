/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:27:50 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/02 20:54:11 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path(char *path)
{
	char	*err_msg;

	if (access(path, F_OK) == -1)
	{
		err_msg = ft_strjoin3("minishell: cd: ", path,
				": No such file or directory");
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
		return (1);
	}
	if (is_dir(path) == 0)
	{
		err_msg = ft_strjoin3("minishell: cd: ", path, ": is not a directory");
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
		return (1);
	}
	if (access(path, X_OK) == -1)
	{
		err_msg = ft_strjoin3("minishell: cd: ", path, ": Permission denied");
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
		return (1);
	}
	return (0);
}

int	ft_cd_home(t_env **env)
{
	int		ret;
	char	*path;

	path = get_env("HOME", *env);
	if (path == NULL && is_in_env("HOME", *env) == 0)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	else
	{
		ft_cd_here(env);
		return (0);
	}
	ret = ft_cd(path, env);
	return (ret);
}

int	ft_cd_oldpwd(t_env **env)
{
	int		ret;
	char	*path;

	path = ft_strdup(get_env("OLDPWD", *env));
	if (path == NULL)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	ret = ft_cd(path, env);
	if (ret == 0)
		ft_putendl_fd(path, 1);
	free(path);
	return (ret);
}

int	ft_cd_here(t_env **env)
{
	char	new_path[PATH_MAX];

	getcwd(new_path, PATH_MAX);
	if (is_in_env("OLDPWD", *env) == 0)
		add_to_env("OLDPWD", new_path, env);
	else
		set_env("OLDPWD", new_path, *env);
	return (0);
}

int	ft_cd(char *path, t_env **env)
{
	char	new_path[PATH_MAX];
	char	*old_path;

	if (check_path(path) == 1)
		return (1);
	old_path = ft_strdup(get_env("PWD", *env));
	if (chdir(path) == -1)
	{
		if (old_path != NULL)
			free(old_path);
		return (1);
	}
	getcwd(new_path, PATH_MAX);
	if (is_in_env("PWD", *env) == 0)
		add_to_env("PWD", new_path, env);
	else
		set_env("PWD", new_path, *env);
	if (is_in_env("OLDPWD", *env) == 0)
		add_to_env("OLDPWD", old_path, env);
	else
		set_env("OLDPWD", old_path, *env);
	if (old_path != NULL)
		free(old_path);
	return (0);
}
