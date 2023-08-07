/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:03:09 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 14:47:27 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_error(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && strs[i][0] != '|')
	{
		if ((strs[i][0] == '>' || strs[i][0] == '<')
			&& (!strs[i + 1] || strs[i + 1][0] == '|'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_file(char **strs, int index)
{
	if (index == 0)
		return (0);
	if (strs[-1][0] == '<' || strs[-1][0] == '>')
		return (1);
	return (0);
}

void	ft_place_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*index;

	if (*cmd == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*cmd = new;
	}
	else
	{
		index = *cmd;
		while (index->next != NULL)
			index = index->next;
		new->next = NULL;
		index->next = new;
		new->prev = index;
	}
}
