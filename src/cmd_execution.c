/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:07:07 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/18 20:09:44 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

int	ft_child_process(int read_fd, int write_fd, char *av, char **env)
{
	int		i;
	char	*cmd;
	char	**allpath;
	char	**av_cmd;

	i = 0;
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
	while (allpath[i])
	{
		cmd = ft_strjoin(allpath[i], av_cmd[0], '/');
		execve(cmd, av_cmd, env);
		free(cmd);
		i++;
	}
	ft_manage_execve_errors(allpath, av_cmd);
	return (-1);
}

void	ft_manage_execve_errors(char **allpath, char **av_cmd)
{
	int	i;

	free(allpath);
	i = 0;
	ft_putstr_fd("Command not found :", 2);
	while (av_cmd[i])
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(av_cmd[i], 2);
		free(av_cmd[i]);
		i++;
	}
	free(av_cmd);
}
// prendre en compte env -i