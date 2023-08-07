/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:45:16 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/13 18:55:16 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *name, char *content, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(name, env->key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(content);
			return ;
		}
		env = env->next;
	}
}
