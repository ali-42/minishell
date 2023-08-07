/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:16:24 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 20:51:44 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_previous(t_cmd *cmd)
{
	cmd = cmd->prev;
	while (cmd != NULL)
	{
		if (cmd->input != 0)
			close(cmd->input);
		if (cmd->output != 1)
			close(cmd->output);
		cmd = cmd->prev;
	}
}

void	free_shell(t_env *env, t_cmd *cmd)
{
	close(0);
	close(1);
	close(2);
	close_previous(cmd);
	free_env(env);
	free_cmd(cmd);
	rl_clear_history();
}
