/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 04:31:01 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/31 04:31:26 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **arg, t_env **env)
{
	int		ret;

	ret = 0;
	if (!arg[1])
		ft_export_noarg(*env, 1);
	else
		ret = ft_export_arg(arg, env);
	return (ret);
}
