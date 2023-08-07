/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:35:32 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/31 04:13:42 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*first_env(t_env *env)
{
	while (env->prev != NULL)
		env = env->prev;
	return (env);
}

static void	del_from_env(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;

	tmp1 = (*env)->prev;
	tmp2 = (*env)->next;
	if (tmp1 != NULL)
		tmp1->next = tmp2;
	if (tmp2 != NULL)
		tmp2->prev = tmp1;
	free((*env)->key);
	free((*env)->value);
	free(*env);
	if (tmp1 == NULL && tmp2 == NULL)
		*env = NULL;
	else if (tmp1 != NULL)
		*env = first_env(tmp1);
	else if (tmp2 != NULL)
		*env = first_env(tmp2);
}

static void	find_to_del(char *arg, t_env **env, t_env **tmp)
{
	while (*env != NULL)
	{
		if (ft_strcmp(arg, (*env)->key) == 0)
		{
			del_from_env(env);
			*tmp = *env;
			break ;
		}
		*tmp = *env;
		*env = (*env)->next;
	}
}

int	ft_unset(char **arg, t_env **env)
{
	int		i;
	int		ret;
	t_env	*tmp;

	i = 1;
	ret = 0;
	tmp = *env;
	while (arg[i] != NULL)
	{
		if (check_invalid_unset(arg[i]) == 1)
			ret = 1;
		else
			find_to_del(arg[i], env, &tmp);
		*env = first_env(tmp);
		i++;
	}
	return (ret);
}
