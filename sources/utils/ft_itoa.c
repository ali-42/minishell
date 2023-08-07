/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:30:55 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/27 20:10:00 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_filtoa(char *num, unsigned int nbr, int n, unsigned int div)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		num[i] = '-';
		i++;
	}
	while (div > 0)
	{
		num[i] = nbr / div + '0';
		nbr = nbr % div;
		div /= 10;
		i++;
	}
	num[i] = '\0';
}

char	*ft_itoa(int n)
{
	unsigned int	div;
	int				size;
	char			*num;
	unsigned int	nbr;

	if (n < 0)
		nbr = (unsigned int)(-n);
	else
		nbr = (unsigned int)n;
	div = 1;
	size = 1;
	while (div <= nbr / 10)
	{
		div *= 10;
		size++;
	}
	if (n < 0)
		size++;
	num = malloc((size + 1) * sizeof(char));
	if (!num)
		return (NULL);
	ft_filtoa(num, nbr, n, div);
	return (num);
}
