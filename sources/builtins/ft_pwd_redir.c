/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 00:02:37 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/30 00:23:54 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd_redir(t_cmd *cmd)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
	{
		ft_putendl_fd("minishell: pwd: error retrieving current directory", 2);
		return (1);
	}
	ft_putendl_fd(path, cmd->output);
	return (0);
}
