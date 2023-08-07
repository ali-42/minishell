/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:35:01 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 21:08:18 by ali              ###   ########.fr       */
/*   Updated: 2022/02/03 19:31:29 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_varname_exit(void)
{
	char	*varname;

	varname = malloc(sizeof(char) * 2);
	if (!varname)
		return (NULL);
	varname[0] = '?';
	varname[1] = '\0';
	return (varname);
}

char	*ft_get_varname(char *str)
{
	char	*varname;
	int		i;

	if (*str == '{')
		str++;
	if (*str == '?')
		return (ft_varname_exit());
	i = 0;
	while (str[i] && !ft_is_vardel(str[i], " ,.?/][}+=-*%$#@!|><\'\"\0"))
		i++;
	varname = malloc(sizeof(char) * (i + 1));
	if (!varname)
		return (NULL);
	i = 0;
	while (str[i] && !ft_is_vardel(str[i], " ,.?/][}+=-*%$#@!|<>\'\"\0"))
	{
		varname[i] = str[i];
		i++;
	}
	varname[i] = '\0';
	return (varname);
}

char	*ft_get_var(char *str, t_env **env, int nospace)
{
	char	*varname;
	char	*value;

	varname = ft_get_varname(str + 1);
	if (!varname)
		return (NULL);
	value = ft_strdup(get_env(varname, *env));
	if (value == NULL && !nospace)
		value = ft_strdup("");
	else if (value == NULL)
		value = ft_strdup("");
	if (value && ft_has_quote(value))
		value = ft_quote_value(value);
	if (value && (value[0] == '>' || value[0] == '<'
			|| value[0] == '|') && nospace)
		value = ft_quote_value(value);
	free(varname);
	return (value);
}

int	ft_variable_size(char *str, t_env **env, int nospace)
{
	char	*var;
	int		i;
	int		size;

	var = ft_get_var(str, env, nospace);
	i = 0;
	size = 0;
	if (!var)
		return (i);
	while (var[i])
	{
		while (var[i] == ' ' && var[i + 1] && var[i + 1] == ' ' && nospace)
			i++;
		if (var[i])
		{
			i++;
			size++;
		}
	}
	free(var);
	return (i);
}

int	ft_pass_variable(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '?')
		return (2);
	if (str[i] == '{')
	{
		while (str[i] && str[i] != '}')
			i++;
		if (str[i])
			return (i + 1);
		return (i);
	}
	i++;
	while (str[i] && !ft_is_vardel(str[i], " ,.?/][{}+=-*%$#@!|<>\'\"\0"))
		i++;
	return (i);
}
