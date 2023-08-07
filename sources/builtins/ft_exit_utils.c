/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:10:03 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/29 21:47:01 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-' || s[0] == '+')
	{
		i++;
		if (s[i] == '\0')
			return (1);
	}
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	is_ll_max(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]) == 1)
	{
		i++;
		j++;
	}
	if (j > 19)
		return (1);
	return (0);
}

static int	check_limits(unsigned long long n, int signe)
{
	if (signe == -1 && n > 9223372036854775808uLL)
		return (1);
	if (signe == 1 && n > 9223372036854775807uLL)
		return (1);
	return (0);
}

int	is_too_large(char *s)
{
	int					i;
	int					signe;
	unsigned long long	n;

	i = 0;
	signe = 1;
	n = 0;
	if (is_ll_max(s) == 1)
		return (1);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(s[i]) == 1)
	{
		n = 10 * n + s[i] - '0';
		i++;
	}
	if (check_limits(n, signe) == 1)
		return (1);
	return (0);
}
