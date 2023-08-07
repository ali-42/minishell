/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 03:32:51 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/28 22:21:18 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_no_arg(t_cmd *cmd, t_env *env)
{
	int		exit_status;
	char	*value;

	value = ft_strdup(get_env("?", env));
	exit_status = ft_atoi(value);
	free(value);
	free_shell(env, cmd);
	ft_putendl_fd("exit", 1);
	exit(exit_status);
}

static void	ft_exit_str(t_cmd *cmd, t_env *env)
{
	char	*err_msg;

	err_msg = ft_strjoin3("minishell: exit: ", cmd->args[1],
			": numeric argument required");
	ft_putendl_fd("exit", 1);
	ft_putendl_fd(err_msg, 2);
	free(err_msg);
	free_shell(env, cmd);
	exit(2);
}

static void	ft_exit_too_many_arg(void)
{
	ft_putendl_fd("exit", 1);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
}

int	ft_exit(t_cmd *cmd, t_env *env)
{
	long long	ret;

	if (cmd->args[1] == NULL)
		ft_exit_no_arg(cmd, env);
	else if (is_str(cmd->args[1]) == 1)
		ft_exit_str(cmd, env);
	else if (is_str(cmd->args[1]) == 0 && cmd->args[2] != NULL)
	{
		ft_exit_too_many_arg();
		return (1);
	}
	else if (is_too_large(cmd->args[1]) == 1)
		ft_exit_str(cmd, env);
	else
	{
		ret = ft_atoi(cmd->args[1]);
		free_shell(env, cmd);
		ft_putendl_fd("exit", 1);
		exit(ret % 256);
	}
	return (0);
}
