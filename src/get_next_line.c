/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:02:10 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/20 13:22:34 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_newline(char *arch, int size)
{
	int		i;
	int		j;
	char	*res;

	j = ft_strlen(arch);
	i = 0;
	if (size == 0)
	{
		free(arch);
		return (NULL);
	}
	while (arch[i] != '\n' && arch[i] != '\0')
		i++;
	if (arch[i] == '\n')
		i++;
	res = malloc(sizeof(char) * (j - i + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (arch[i])
		res[j++] = arch[i++];
	res[j] = '\0';
	free(arch);
	return (res);
}

char	*ft_row(char *arch)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (arch[len] != '\n' && arch[len] != '\0')
		len++;
	if (arch[len] == '\n')
		len++;
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (++i < len)
		res[i] = arch[i];
	res[i] = '\0';
	if (!len)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	*ft_strjoin(char *s1, char *s2, char sep)
{
	int		i;
	int		j;
	int		len;
	char	*s3;

	len = 1;
	j = -1;
	i = -1;
	if (!s1)
		s1 = ft_empty_str(0);
	if (!s1 || !s2)
		return (NULL);
	if (!sep)
		len = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + len + 1));
	if (!s3)
		return (NULL);
	while (s1[++i])
		s3[i] = s1[i];
	s3[i] = sep;
	i += len;
	while (s2[++j])
		s3[j + i] = s2[j];
	s3[j + i] = '\0';
	return (free(s1), s3);
}

char	*get_next_line(int fd)
{
	ssize_t		size;
	static char	*arch;
	char		*buff;

	size = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (size != 0 && (!ft_gotcha(arch)))
	{
		buff = ft_empty_str(BUFFER_SIZE);
		if (!buff)
			return (NULL);
		size = read(fd, buff, BUFFER_SIZE);
		if (size < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[size] = '\0';
		arch = ft_strjoin(arch, buff, 0);
	}
	buff = ft_row(arch);
	arch = ft_newline(arch, size);
	return (buff);
}
