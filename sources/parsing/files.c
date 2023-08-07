/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:44:05 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 19:22:55 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_file(t_file **files, int type, char *name)
{
	t_file	*new;
	t_file	*index;

	new = malloc(sizeof(t_file));
	if (new == NULL)
		return ;
	new->type = type;
	new->name = ft_strdup(name);
	if (*files == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*files = new;
	}
	else
	{
		index = *files;
		while (index->next != NULL)
			index = index->next;
		new->next = NULL;
		new->prev = index;
		index->next = new;
	}
}

void	ft_before_cmd(t_cmd *cmd, char **strs, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (!ft_is_separator(strs[i][0]) && ft_is_file(strs + i, i))
		{
			if (strs[i - 1][0] == '<')
			{
				if (strs[i - 1][1] && strs[i - 1][1] == '<')
					ft_add_file(&cmd->infile, HEREDOC, strs[i]);
				else
					ft_add_file(&cmd->infile, INFILE, strs[i]);
			}
			if (strs[i - 1][0] == '>')
			{
				if (strs[i - 1][1] && strs[i - 1][1] == '>')
					ft_add_file(&cmd->outfile, APPEND, strs[i]);
				else
					ft_add_file(&cmd->outfile, REPLACE, strs[i]);
			}
		}
		i++;
	}
}

void	ft_after_cmd(t_cmd *cmd, char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && strs[i][0] != '|')
	{
		if (!ft_is_separator(strs[i][0]) && ft_is_file(strs + i, i))
		{
			if (strs[i - 1][0] == '<')
			{
				if (strs[i - 1][1] && strs[i - 1][1] == '<')
					ft_add_file(&cmd->infile, HEREDOC, strs[i]);
				else
					ft_add_file(&cmd->infile, INFILE, strs[i]);
			}
			if (strs[i - 1][0] == '>')
			{
				if (strs[i - 1][1] && strs[i - 1][1] == '>')
					ft_add_file(&cmd->outfile, APPEND, strs[i]);
				else
					ft_add_file(&cmd->outfile, REPLACE, strs[i]);
			}
		}
		i++;
	}
}

void	ft_set_pipe(t_cmd *cmd, char **strs, int index)
{
	int	i;

	i = 0;
	if (cmd->infile == NULL && index != 0)
		ft_add_file(&cmd->infile, PIPE, NULL);
	while (strs[i] && strs[i][0] != '|')
		i++;
	if (cmd->outfile == NULL && strs[i])
		ft_add_file(&cmd->outfile, PIPE, NULL);
}

int	ft_filetype(t_cmd *cmd, char **strs, int index)
{
	int		i;
	int		j;
	t_file	*infile;
	t_file	*outfile;

	infile = NULL;
	outfile = NULL;
	i = 0;
	j = 0;
	while (cmd->next != NULL)
		cmd = cmd->next;
	cmd->infile = infile;
	cmd->outfile = outfile;
	while (index > 0 && strs[j][0] != '|')
	{
		j--;
		index--;
	}
	ft_before_cmd(cmd, &strs[j], -j);
	ft_after_cmd(cmd, &strs[i]);
	ft_set_pipe(cmd, strs, index);
	while (strs[i] && !ft_is_separator(strs[i][0]))
		i++;
	return (i);
}
