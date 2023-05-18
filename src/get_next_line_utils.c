/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:14:57 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/04 14:59:22 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_empty_str(int len)
{
	char	*str;

	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (len >= 0)
	{
		str[len] = '\0';
		len--;
	}
	return (str);
}

int	ft_strlen(char *str)
{
	int	j;

	j = 0;
	while (str[j])
		j++;
	return (j);
}

int	ft_gotcha(char *arch)
{
	int	i;

	i = 0;
	if (!arch)
		return (0);
	while (arch[i])
	{
		if (arch[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
