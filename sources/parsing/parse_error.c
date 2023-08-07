/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:18:57 by ali               #+#    #+#             */
/*   Updated: 2022/02/02 02:33:22 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_end_error(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && strs[i + 1])
		i++;
	if (strs[i] && (strs[i][0] == '>' || strs[i][0] == '<'
			|| strs[i][0] == '|'))
		return (1);
	return (0);
}

int	ft_pipe_nocmd(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && strs[i + 1])
	{
		if (!ft_is_file(&strs[i], i) && !ft_is_separator(strs[i][0]))
			return (0);
		i++;
	}
	if (strs[i] && strs[i][0] == '|')
		return (1);
	return (0);
}

int	ft_conjoin_error(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if ((strs[i][0] == '<' || strs[i][0] == '>') && strs[i + 1]
			&& ft_is_separator(strs[i + 1][0]))
			return (1);
		if (strs[i][0] == '|' && strs[i + 1] && strs[i + 1][0] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	ft_quote_error(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			while (strs[i][j] && strs[i][j] != '\"' && strs[i][j] != '\'')
				j++;
			if (!strs[i][j])
				break ;
			if (!ft_quote_closed(&strs[i][j]))
				return (1);
			j += ft_pass_quote(&strs[i][j]);
		}
		i++;
	}
	return (0);
}

int	ft_parse_error(char **strs)
{
	if (ft_conjoin_error(strs))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return (1);
	}
	if (ft_pipe_nocmd(strs) || (strs[0] && strs[0][0] == '|'))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return (1);
	}
	if (ft_end_error(strs) || (strs[0]
			&& (strs[0][0] == '>' || strs[0][0] == '<') && !strs[1]))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return (1);
	}
	if (ft_quote_error(strs))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return (1);
	}
	return (0);
}
