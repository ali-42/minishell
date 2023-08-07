/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   already_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:21:57 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 20:48:58 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	already_open_file(t_file *file, char *name)
{
	while (file != NULL)
	{
		if (file->type == APPEND || file->type == REPLACE)
			if (ft_strcmp(name, file->name) == 0 && access(name, F_OK) == 0)
				return (1);
		file = file->next;
	}
	return (0);
}

int	already_open(t_cmd *cmd, char *name)
{
	cmd = cmd->prev;
	while (cmd != NULL)
	{
		if (cmd->outfile != NULL)
			if (already_open_file(cmd->outfile, name) == 1)
				return (1);
		cmd = cmd->prev;
	}
	return (0);
}

static int	get_outfile_fd(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_APPEND | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fd);
}

int	get_fd(t_cmd *cmd, char *name)
{
	while (cmd != NULL)
	{
		if (already_open_file(cmd->outfile, name) == 1)
			return (get_outfile_fd(name));
		cmd = cmd->prev;
	}
	return (0);
}
