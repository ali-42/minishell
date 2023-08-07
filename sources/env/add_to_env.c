/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:59:13 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/21 20:07:56 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(char *name, char *content, t_env **env)
{
	t_env	*new;
	t_env	*index;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return ;
	new->key = ft_strdup(name);
	new->value = ft_strdup(content);
	if (*env == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*env = new;
	}
	else
	{
		index = *env;
		while (index->next != NULL)
			index = index->next;
		new->next = NULL;
		new->prev = index;
		index->next = new;
	}
}
