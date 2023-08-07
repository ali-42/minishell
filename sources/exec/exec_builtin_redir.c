/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:38:29 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 15:15:42 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ret = ft_cd_oldpwd_redir(cmd, env);
	else if (ft_strcmp(cmd->args[1], "..") == 0)
		ret = ft_cd_back(env);
	else if (ft_strcmp(cmd->args[1], ".") == 0)
		ret = ft_cd_here(env);
	else if (cmd->args[1] == NULL || ft_strcmp(cmd->args[1], "~") == 0)
		ret = ft_cd_home(env);
	else
		ret = ft_cd_path_redir(cmd->args[1], env, cmd->output);
	return (ret);
}

static int	exec_echo(t_cmd *cmd)
{
	int	ret;

	if (!cmd->args[1])
	{
		write(cmd->output, "\n", 1);
		return (0);
	}
	if (is_n(cmd->args[1]) == 1)
		ret = ft_echo_redir(cmd->args, cmd->output, 1);
	else
		ret = ft_echo_redir(cmd->args, cmd->output, 0);
	return (ret);
}

void	exec_builtin_redir(t_cmd *cmd, t_env **env)
{
	int		ret;

	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ret = exec_echo(cmd);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		ret = exec_cd(cmd, env);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ret = ft_pwd_redir(cmd);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		ret = ft_export_redir(cmd->args, env, cmd->output);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		ret = ft_unset(cmd->args, env);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		ret = ft_env_redir(cmd, *env);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		ret = ft_exit(cmd, *env);
	g_exit = ret;
}
