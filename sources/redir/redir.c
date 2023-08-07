/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:15:20 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/01 03:35:59 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_cmd *cmd)
{
	if (cmd->prev != NULL)
		close(cmd->prev->pipe_output);
	if (cmd->next != NULL)
		close(cmd->next->pipe_input);
	if (cmd->infile != NULL)
		if (cmd->infile->type != PIPE && cmd->prev != NULL)
			close(cmd->pipe_input);
	if (cmd->outfile != NULL)
		if (cmd->outfile->type != PIPE && cmd->next != NULL)
			close(cmd->pipe_output);
}

static void	redirect_input(t_cmd *cmd)
{
	if (cmd->infile != NULL)
	{
		if (cmd->infile->type == PIPE)
		{
			dup2(cmd->pipe_input, STDIN_FILENO);
			close(cmd->pipe_input);
		}
		else if (cmd->input != 0)
		{
			dup2(cmd->input, STDIN_FILENO);
			close(cmd->input);
		}
	}
	else if (cmd->input != 0)
	{
		dup2(cmd->input, STDOUT_FILENO);
		close(cmd->input);
	}
}

static void	redirect_output(t_cmd *cmd)
{
	if (cmd->outfile != NULL)
	{
		if (cmd->outfile->type == PIPE)
		{
			dup2(cmd->pipe_output, STDOUT_FILENO);
			close(cmd->pipe_output);
		}
		else if (cmd->output != 1)
		{
			dup2(cmd->output, STDOUT_FILENO);
			close(cmd->output);
		}
	}
	else if (cmd->output != 1)
	{
		dup2(cmd->output, STDOUT_FILENO);
		close(cmd->output);
	}
}

void	redir(t_cmd *cmd)
{
	close_fd(cmd);
	redirect_input(cmd);
	redirect_output(cmd);
}
