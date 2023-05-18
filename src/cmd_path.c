/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:49:08 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/18 19:50:22 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	int		i;
	char	*path;
	char	**allpaths;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != 0)
		{
			path = ft_strnstr(env[i], "PATH=", 5);
			allpaths = ft_split(path, ':');
			return (allpaths);
		}
		i++;
	}	
	return (NULL);
}
