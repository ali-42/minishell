/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:48:49 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/28 17:07:38 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_cmd *cmd)
{
	int	fd[2];

	if (cmd->next == NULL)
		return ;
	if (pipe(fd) == -1)
	{
		ft_putendl_fd("minishell: pipe failed", 2);
		return ;
	}
	cmd->pipe_output = fd[1];
	cmd->next->pipe_input = fd[0];
}
