/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_execve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:59:23 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/02 18:59:55 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell_execve(t_env *env, t_cmd *cmd)
{
	free_env(env);
	free_cmd(cmd);
	rl_clear_history();
}
