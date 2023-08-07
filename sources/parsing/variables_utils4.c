/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:19:32 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 23:19:50 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_loop(char *key, char *value)
{
	int	i;
	int	j;

	i = 0;
	while (value[i])
	{
		j = 0;
		while (key[j] && value[i + j] && key[j] == value[i + j])
			j++;
		if (!key[j])
			return (1);
		i++;
	}
	return (0);
}

int	ft_pass_loop(char *str, t_env **env, int *indic)
{
	char	*varname;
	char	*value;
	int		i;

	i = 0;
	while (str[i] && (!ft_is_variable(&str[i]) || indic[0] == 1))
	{
		ft_check_quotes(str[i], indic);
		i++;
	}
	if (str[i] && ft_is_variable(&str[i]) && indic[0] == 0)
	{
		varname = ft_get_varname(&str[i] + 1);
		value = ft_get_var(&str[i], env, indic[1]);
		if (is_loop(varname, value))
		{
			free(value);
			free(varname);
			return (i + ft_pass_variable(&str[i]));
		}
		free(value);
		free(varname);
		return (i);
	}
	return (i);
}

int	next_var(char *str, int	*nospace)
{
	int	novar;
	int	i;

	novar = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && novar == 0 && *nospace)
			novar = 1;
		else if (str[i] == '\'' && novar == 1 && *nospace)
			novar = 0;
		if (str[i] == '\"' && *nospace == 0 && !novar)
			*nospace = 1;
		else if (str[i] == '\"' && *nospace == 1 && !novar)
			*nospace = 0;
		if (ft_is_variable(&str[i]) && novar == 0)
			return (i);
		else
			i++;
	}
	return (i);
}

int	fill_no_var(char *str, char *sub, int *nospace)
{
	int	novar;
	int	i;

	novar = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && novar == 0 && *nospace)
			novar = 1;
		else if (str[i] == '\'' && novar == 1 && *nospace)
			novar = 0;
		if (str[i] == '\"' && *nospace == 0 && !novar)
			*nospace = 1;
		else if (str[i] == '\"' && *nospace == 1 && !novar)
			*nospace = 0;
		if (ft_is_variable(&str[i]) && novar == 0)
			return (i);
		else
		{
			sub[i] = str[i];
			i++;
		}
	}
	return (i);
}
