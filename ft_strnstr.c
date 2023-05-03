/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:06:09 by tbourdea          #+#    #+#             */
/*   Updated: 2023/02/19 17:59:02 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (len == 0 && (!big || !little))
		return (NULL);
	if (little[j] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i + j] == little[j])
		{
			if (little[j + 1] == '\0' && i + j < len)
				return ((char *)&big[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	(void) ac;
	printf("Ma Fonction : %s\n", ft_strnstr(av[1], av[2], 5));
	// printf("Ma Fonction : %s\n", strnstr(((void *)0), "fake", 0));
	return (0);
}
//Finit.
