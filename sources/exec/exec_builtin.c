/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:15:26 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 20:39:30 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n(char *s)
{
	int	i;

	i = 1;
	if (s[0] && s[0] == '-')
	{
		while (s[i] != '\0')
		{
			if (s[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static int	check_too_many(char **args)
{
	if (args[1] != NULL)
		if (args[2] != NULL)
			return (1);
	return (0);
}

static int	exec_cd(t_cmd *cmd, t_env **env)
{
	int	ret;

	if (check_too_many(cmd->args) == 1)
		ret = ft_cd_too_many();
	else if (ft_strcmp(cmd->args[1], "-") == 0)
		ret = ft_cd_oldpwd(env);
	else if (ft_strcmp(cmd->args[1], "..") == 0)
		ret = ft_cd_back(env);
	else if (ft_strcmp(cmd->args[1], ".") == 0)
		ret = ft_cd_here(env);
	else if (cmd->args[1] == NULL || ft_strcmp(cmd->args[1], "~") == 0)
		ret = ft_cd_home(env);
	else
		ret = ft_cd_path(cmd->args[1], env);
	return (ret);
}

static int	exec_echo(t_cmd *cmd)
{
	int	ret;

	if (!cmd->args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (is_n(cmd->args[1]) == 1)
		ret = ft_echo(cmd->args, 1);
	else
		ret = ft_echo(cmd->args, 0);
	return (ret);
}

void	exec_builtin(t_cmd *cmd, t_env **env)
{
	int		ret;

	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ret = exec_echo(cmd);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		ret = exec_cd(cmd, env);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ret = ft_pwd();
	if (ft_strcmp(cmd->args[0], "export") == 0)
		ret = ft_export(cmd->args, env);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		ret = ft_unset(cmd->args, env);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		ret = ft_env(*env);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		ret = ft_exit(cmd, *env);
	if (cmd->next != NULL || cmd->prev != NULL)
	{
		close(5);
		free_shell(*env, cmd);
		exit(ret);
	}
	g_exit = ret;
}
