/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 20:36:06 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_cmd *cmd)
{
	if (cmd->prev != NULL)
	{
		close(cmd->pipe_input);
		close(cmd->prev->pipe_output);
	}
}

void	set_last_cmd(t_cmd *cmd, t_env **env)
{
	char	**path;
	char	*full_path;

	path = ft_split(get_env("PATH", *env), ':');
	full_path = get_path(cmd, path);
	free_char2(path);
	if (full_path)
	{
		if (is_in_env("_", *env))
			set_env("_", full_path, *env);
		else
			add_to_env("_", full_path, env);
		free(full_path);
	}
	else
	{
		if (is_in_env("_", *env))
			set_env("_", cmd->args[0], *env);
		else
			add_to_env("_", cmd->args[0], env);
	}
}

static void	manage_cmd(t_cmd *cmd, t_env **env, int *builtin)
{
	cmd->pid = 1;
	if (is_builtin(cmd->args[0]) == 1
		&& cmd->next == NULL && cmd->prev == NULL)
	{
		*builtin = 1;
		if (check_redir_error(cmd))
			return ;
		set_last_cmd(cmd, env);
		if (cmd->outfile != NULL)
			exec_builtin_redir(cmd, env);
		else
			exec_builtin(cmd, env);
	}
	else if (cmd->args[0] != NULL)
	{
		set_last_cmd(cmd, env);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			ft_signal(3);
			exec_cmd(cmd, env);
		}
	}
}

void	ft_exit_status(int exit_status, int builtin)
{
	if (exit_status == 2)
		g_exit = 130;
	else if (exit_status == 131)
		g_exit = 131;
	else if (builtin == 0)
		g_exit = exit_status >> 8;
}

void	exec_all_cmd(t_cmd *cmd, t_env **env)
{
	int		exit_status;
	int		builtin;
	t_cmd	*begin;

	exit_status = 0;
	builtin = 0;
	begin = cmd;
	if (ft_prep_heredoc(cmd, &exit_status) == 0)
		return ;
	while (cmd != NULL)
	{
		cmd->parent = getpid();
		create_pipe(cmd);
		if (check_file(cmd->infile, cmd->outfile, cmd) == 1)
		{
			g_exit = -1;
			manage_cmd(cmd, env, &builtin);
			close_fd(cmd);
			waitpid(cmd->pid, &exit_status, 0);
			ft_exit_status(exit_status, builtin);
		}
		close_fd(cmd);
		cmd = cmd->next;
	}
	close_and_destroy(begin);
}
