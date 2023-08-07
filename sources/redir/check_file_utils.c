/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:31:53 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 20:54:18 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	send_err_msg(char *name, char mode)
{
	char	*err_msg;

	if (mode == 'F')
		err_msg = ft_strjoin3("minishell: ",
				name, ": No such file or directory");
	if (mode == 'R')
		err_msg = ft_strjoin3("minishell: ", name, ": Permission denied");
	if (mode == 'W')
		err_msg = ft_strjoin3("minishell: ", name, ": Permission denied");
	if (mode == 'O')
		err_msg = ft_strjoin3("minishell: ", name, ": Permission denied");
	if (err_msg != NULL)
	{
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
		g_exit = 1;
	}
}

int	stock_fd(int fd, t_cmd *cmd, t_file *outfile)
{
	if (fd == -1)
	{
		send_err_msg(outfile->name, 'O');
		return (0);
	}
	if (outfile->next == NULL)
		cmd->output = fd;
	else
		close(fd);
	return (1);
}
