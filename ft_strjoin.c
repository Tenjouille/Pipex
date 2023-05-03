/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:24:20 by tbourdea          #+#    #+#             */
/*   Updated: 2022/11/19 10:55:53 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		s3[j + i] = s2[i];
		i++;
	}
	s3[j + i] = '\0';
	return (s3);
}
/*
int	main(int ac, char **av)
{
	(void) ac;
	printf("%s\n", ft_strjoin(av[1], av[2]));
	printf("Taille de la chaine : %d\n", ft_strlen(ft_strjoin(av[1], av[2])));
	return (0);
}*/
