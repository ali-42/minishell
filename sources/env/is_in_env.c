/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:54:57 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/13 18:54:36 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_env(char *name, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
