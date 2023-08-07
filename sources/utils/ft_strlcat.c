/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:04:56 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/10 17:05:53 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlcat(char *dst, char *src, int len)
{
	int	i;

	i = ft_strlen(dst);
	if (i >= len)
		return (len + ft_strlen(src));
	ft_strlcpy(dst + i, src, len - i);
	return (i + ft_strlen(src));
}
