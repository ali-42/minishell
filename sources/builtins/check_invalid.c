/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 08:14:07 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/31 05:01:54 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	send_err_msg_export(char *s)
{
	char	*err_msg;

	err_msg = ft_strjoin3("minishell: export: ",
			s, ": not a valid identifier");
	ft_putendl_fd(err_msg, 2);
	free(err_msg);
}

int	check_invalid_export(char *s)
{
	int	i;

	i = 1;
	if (!((s[0] <= 'z' && s[0] >= 'a') || (s[0] <= 'Z' && s[0] >= 'A')
			|| s[0] == '_'))
	{
		send_err_msg_export(s);
		return (1);
	}
	while (s[i] != '\0' && s[i] != '=')
	{
		if (!((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A')
				|| (s[i] <= '9' && s[i] >= '0') || s[i] == '_'))
		{
			if (!(s[i] == '+' && s[i + 1] == '='))
			{
				send_err_msg_export(s);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static void	send_err_msg_unset(char *s)
{
	char	*err_msg;

	err_msg = ft_strjoin3("minishell: unset: ",
			s, ": not a valid identifier");
	ft_putendl_fd(err_msg, 2);
	free(err_msg);
}

int	check_invalid_unset(char *s)
{
	int	i;

	i = 1;
	if (!((s[0] <= 'z' && s[0] >= 'a') || (s[0] <= 'Z' && s[0] >= 'A')
			|| s[0] == '_'))
	{
		send_err_msg_unset(s);
		return (1);
	}
	while (s[i] != '\0')
	{
		if (!((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A')
				|| (s[i] <= '9' && s[i] >= '0') || s[i] == '_'))
		{
			send_err_msg_unset(s);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_export_add(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=' && s[i] != '\0')
		i++;
	if (s[i] == '=')
		if (i != 0)
			if (s[i - 1] == '+')
				return (1);
	return (0);
}
