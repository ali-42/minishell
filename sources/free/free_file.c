/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:07:43 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/01 09:43:58 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_file(t_file *file)
{
	t_file	*tmp;

	if (file == NULL)
		return ;
	while (file->prev)
		file = file->prev;
	while (file != NULL)
	{
		tmp = file->next;
		if (file->name != NULL)
			free(file->name);
		free(file);
		file = tmp;
	}
}
