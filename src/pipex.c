/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:58:46 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/18 20:05:39 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

char	*ft_sepwords(char **dest, char const *s, int c, int j)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (s[size] != '\0' && s[size] != c)
		size++;
	dest[j] = malloc(sizeof(char) * (size + 1));
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
	dest[j][i] = '\0';
	return (dest[j]);
}

char	**ft_split(char const *s, char c)
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
		dest[j] = ft_sepwords(dest, &s[i], c, j);
		while (s[i] != '\0' && s[i] != c)
			i++;
		while (s[i] == c)
			i++;
		j++;
	}
	dest[ft_mallocsize(s, c)] = 0;
	return (dest);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*s3;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	j = 0;
// 	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!s3)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		s3[j] = s1[i];
// 		i++;
// 		j++;
// 	}
// 	i = 0;
// 	while (s2[i])
// 	{
// 		s3[j + i] = s2[i];
// 		i++;
// 	}
// 	s3[j + i] = '\0';
// 	return (s3);
// }

int	main(int ac, char **av, char **env)
{
	int		j;
	int		fd_infile;
	int		fd_outfile;
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (!ft_parsing(ac, av))
		return (1);
	// if (ft_parsing == -1)
	// 	ft_here_doc();
	j = 2;
	fd_infile = open(av[1], O_RDONLY);
	fd_outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
	{
		if (dup2(fd_outfile, 2) == -1)
			return (-1);
		close (fd_outfile);
		write (2, "0\n", 2);
		return (0);
	}
	if (fd_outfile < 0)
		return (1);
	while (j < ac - 1)
	{
		pipe(pipe_fd);
		pid = fork();
		if (pid == -1)
			return (write(2, "Fork Error\n", 11), 0);
		if (pid == 0)
		{
			if (j == ac -2)
			{
				// write(2, "Last Process\n", 13);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
				if (ft_child_process(fd_infile, fd_outfile, av[ac - 2], env) == -1)
					return (127);
			}
			else
			{
				close(pipe_fd[0]);
				// write(2, "First Process\n", 14);
				if (ft_child_process(fd_infile, pipe_fd[1], av[j], env) == -1)
					return (127);
			}
		}
		else
		{
			close(pipe_fd[1]);
			close(fd_infile);
			fd_infile = pipe_fd[0];
			j++;
		}
	}
	close (pipe_fd[0]);
	wait (&status);
	wait (&status);
	return (WEXITSTATUS(status));
}
