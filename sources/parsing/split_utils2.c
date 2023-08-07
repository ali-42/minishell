/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 08:52:35 by ali               #+#    #+#             */
/*   Updated: 2022/01/31 09:00:11 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pass_quote_word(char *str)
{
	int	i;

	i = 0;
	i += ft_pass_quote(&str[i]);
	if (str[i] && str[i] != ' ' && !ft_is_separator(str[i]))
		return (i + ft_pass_word(&str[i]));
	else
		return (i);
}
