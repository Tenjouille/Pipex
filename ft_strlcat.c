/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:57:28 by tbourdea          #+#    #+#             */
/*   Updated: 2022/11/18 10:08:48 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	dstlen = 0;
	if (n == 0 && (!dst || !src))
		return (dstlen);
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (n <= dstlen)
		return (n + srclen);
	j = 0;
	i = dstlen;
	while (src[j] && (i + j) < n)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (n <= i + j)
		j--;
	dst[i + j] = '\0';
	return (dstlen + srclen);
}
/*
int	main(void)
{
	char	*Nul1 = NULL;

	printf("Jesus : %ld\n", ft_strlcat(Nul1, "Salut", 3));
	printf("%s", "\0");
	return (0);
}
*/