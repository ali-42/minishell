/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 07:45:02 by ali               #+#    #+#             */
/*   Updated: 2022/02/02 02:36:28 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_heredoc(int fd)
{
	int		bytes;
	char	buffer[4097];
	char	*heredoc;
	char	*tmp;

	heredoc = NULL;
	bytes = read(fd, buffer, 4096);
	while (bytes)
	{
		if (bytes == -1)
			return (NULL);
		buffer[bytes] = '\0';
		tmp = ft_strjoin(buffer, heredoc);
		free(heredoc);
		heredoc = tmp;
		bytes = read(fd, buffer, 4096);
	}
	return (heredoc);
}

char	*ft_read_heredoc(t_file *file)
{
	char	*line;
	char	*heredoc;
	char	*tmp;

	line = readline("> ");
	heredoc = NULL;
	while (line != NULL)
	{
		if (ft_strcmp(line, file->name) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_join(heredoc, line);
		free(heredoc);
		heredoc = tmp;
		free(line);
		line = readline("> ");
	}
	return (heredoc);
}

int	ft_prep_heredoc(t_cmd *cmd, int *exit_status)
{
	t_file	*begin;
	int		status;
	t_cmd	*begin_cmd;

	status = g_exit;
	g_exit = -1;
	begin_cmd = cmd;
	while (cmd != NULL)
	{
		begin = cmd->infile;
		create_all_heredoc(cmd->infile, exit_status);
		cmd->infile = begin;
		cmd = cmd->next;
	}
	if (g_exit != 130)
	{
		g_exit = status;
		return (1);
	}
	ft_destroy_heredoc(begin_cmd);
	return (0);
}

void	ft_destroy_heredoc(t_cmd *cmd)
{
	int		fd;
	t_file	*begin;

	while (cmd != NULL)
	{
		begin = cmd->infile;
		while (cmd->infile)
		{
			if (cmd->infile->type == HEREDOC)
			{
				fd = open(cmd->infile->name, O_RDONLY);
				if (fd != -1)
				{
					close(fd);
					unlink(cmd->infile->name);
				}
			}
			cmd->infile = cmd->infile->next;
		}
		cmd->infile = begin;
		cmd = cmd->next;
	}
}
