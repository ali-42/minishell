/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 09:05:24 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 21:09:02 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_not_spaces(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **arg, int mode)
{
	int	i;

	i = 1;
	while (mode == 1 && arg[i] && is_n(arg[i]))
		i++;
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1] != NULL && is_not_spaces(arg[i]))
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (mode == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
