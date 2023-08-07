/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 00:03:42 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/30 00:24:12 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_redir(t_cmd *cmd, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "?") != 0)
		{
			ft_putstr_fd(env->key, cmd->output);
			ft_putstr_fd("=", cmd->output);
			if (env->value != NULL)
				ft_putendl_fd(env->value, cmd->output);
			else
				ft_putstr_fd("\n", cmd->output);
		}
		env = env->next;
	}
	return (0);
}
