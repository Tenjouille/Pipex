/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:49:08 by tbourdea          #+#    #+#             */
/*   Updated: 2023/02/21 13:33:53 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freeall(char **dest, int j)
{
	while (j >= 0)
	{
		free(dest[j]);
		j--;
	}
	free(dest);
}

int	ft_mallocsize(char const *s, char c)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	if (s[0] == '\0')
		return (0);
	if (c == '\0')
		return (1);
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		if (s[i + 1] == '\0' || s[i + 1] == c)
		{
			size++;
			while (s[i + 1] == c)
				i++;
		}
		i++;
	}
	return (size);
}

char	*ft_sepwords_w_slash(char **dest, char const *s, int c, int j)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (s[size] != '\0' && s[size] != c)
		size++;
	dest[j] = malloc(sizeof(char) * (size + 2));
	if (!dest[j])
	{
		ft_freeall(dest, j - 1);
		return (NULL);
	}
	while (s[i] != c && s[i] != '\0')
	{
		dest[j][i] = s[i];
		i++;
	}
	dest[j][i] = '/';
	dest[j][i + 1] = '\0';
	return (dest[j]);
}

char	**ft_split_w_slash(char const *s, char c)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_mallocsize(s, c) + 1));
	if (!dest)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (j < ft_mallocsize(s, c))
	{
		dest[j] = ft_sepwords_w_slash(dest, &s[i], c, j);
		while (s[i] != '\0' && s[i] != c)
			i++;
		while (s[i] == c)
			i++;
		j++;
	}
	dest[ft_mallocsize(s, c)] = 0;
	return (dest);
}

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

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
				return ((char *)&big[i + j + 1]);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

char	**ft_allpaths(char **env)
{
	int		len;
	int		i;
	char	*path;
	char	**allpaths;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != 0)
		{
			len = ft_strlen(ft_strnstr(env[i], "PATH=", 5));
			path = malloc(sizeof(char) * len + 1);
			if (!path)
				return (0);
			path = ft_strnstr(env[i], "PATH=", 5);
			break ;
		}
		i++;
	}	
	allpaths = ft_split_w_slash(path, ':');
	i = 0;
	return (allpaths);
}