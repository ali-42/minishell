/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:25:38 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/29 23:25:52 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "?") != 0)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			if (env->value != NULL)
				ft_putendl_fd(env->value, 1);
			else
				ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}
