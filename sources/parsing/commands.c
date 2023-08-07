/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:42:46 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 15:02:38 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(char **strs)
{
	int	i;
	int	args_nb;

	i = 0;
	args_nb = 0;
	while (strs[i] && strs[i][0] != '|')
	{
		if (!ft_is_separator(strs[i][0]) && !ft_is_file(&strs[i], i))
			args_nb++;
		i++;
	}
	return (args_nb);
}

void	ft_fill_args(char **strs, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i] && strs[i][0] != '|')
	{
		if (!ft_is_separator(strs[i][0]) && !ft_is_file(&strs[i], i))
		{
			args[j] = ft_strdup(strs[i]);
			j++;
		}
		i++;
	}
}

void	ft_add_cmd(t_cmd **cmd, char **strs)
{
	t_cmd	*new;
	int		args_nb;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	args_nb = ft_count_args(strs);
	new->args = malloc(sizeof(char *) * (args_nb + 1));
	if (!new->args)
		return ;
	ft_fill_args(strs, new->args);
	new->args[args_nb] = NULL;
	new->input = 0;
	new->output = 1;
	new->pipe_input = 0;
	new->pipe_output = 1;
	new->redir_error = 0;
	new->redir_error = ft_redir_error(strs);
	ft_place_cmd(cmd, new);
}

void	ft_remove_cmdquote(t_cmd *cmd)
{
	int		i;
	t_cmd	*begin;
	char	**args;

	begin = cmd;
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->args[i])
		{
			args = cmd->args;
			if ((args[i][0] == '\"' || args[i][0] == '\'')
				&& args[i][1] && ft_is_separator(args[i][1]))
				args[i] = ft_remove_quote(args[i], 0);
			i++;
		}
		cmd = cmd->next;
	}
	cmd = begin;
}

t_cmd	*ft_stock_cmd(char **strs)
{
	t_cmd	*cmd;
	int		i;

	if (strs[0] == NULL)
		return (NULL);
	cmd = NULL;
	i = 0;
	while (strs[i])
	{
		ft_add_cmd(&cmd, &strs[i]);
		ft_filetype(cmd, &strs[i], i);
		while (strs[i] && strs[i][0] != '|')
			i++;
		if (strs[i])
			i++;
	}
	ft_remove_cmdquote(cmd);
	return (cmd);
}
