/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:07:07 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/20 15:05:21 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

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

int	ft_child_process(int read_fd, int write_fd, char *av, char **env)
{
	int		i;
	char	*cmd;
	char	**allpath;
	char	**av_cmd;

	i = -1;
	allpath = ft_allpaths(env);
	av_cmd = ft_split(av, ' ');
	if (dup2(read_fd, 0) == -1)
		return (-1);
	close (read_fd);
	if (dup2(write_fd, 1) == -1)
		return (-1);
	close (write_fd);
	if (!access(av_cmd[0], F_OK))
		execve(av_cmd[0], av_cmd, env);
	if (!allpath)
		return (ft_manage_execve_errors(allpath, av_cmd), -1);
	while (allpath[++i])
	{
		cmd = ft_strjoin(allpath[i], av_cmd[0], '/');
		execve(cmd, av_cmd, env);
		free(cmd);
	}
	return (ft_manage_execve_errors(allpath, av_cmd), -1);
}

void	ft_manage_execve_errors(char **allpath, char **av_cmd)
{
	int		i;
	char	*cmd_not_found;

	i = 0;
	cmd_not_found = ft_strdup("Command not found : ");
	while (av_cmd[i])
	{
		cmd_not_found = ft_strjoin(cmd_not_found, av_cmd[i], 0);
		if (av_cmd[i + 1])
			cmd_not_found = ft_strjoin(cmd_not_found, " ", 0);
		free(av_cmd[i]);
		i++;
	}
	cmd_not_found = ft_strjoin(cmd_not_found, "\n", 0);
	ft_putstr_fd(cmd_not_found, 2);
	free(cmd_not_found);
	free(allpath);
	free(av_cmd);
}

char	*ft_strdup(char *s)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
