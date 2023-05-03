/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:07:07 by tbourdea          #+#    #+#             */
/*   Updated: 2023/03/02 16:02:29 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line/get_next_line.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

int	ft_child_process(int read_fd, int write_fd, char *av, char **env)
{//CLOSE LE BOUT DE TUBE NON UTILISE AVANT DE RENTRER DANS LA FONCTION !!
	int		i;
	char	*cmd;
	char	**allpath;
	char	**av_cmd;
	char	*print;

	i = 0;
	allpath = ft_allpaths(env);
	av_cmd = ft_split(av, ' ');
	close (0);
	if (dup2(read_fd, 0) == -1)
		return (write(2, "Dup Error num 1\n", 16), -1);
	close (1);
	if (dup2(write_fd, 1) == -1)
		return (write(2, "Dup Error num 2\n", 16), -1);
	while (allpath[i])
	{
		cmd = ft_strjoin(allpath[i], av_cmd[0]);
		execve (cmd, av_cmd, env);
		// free(cmd);
		i++;
	}
	print = get_next_line(read_fd);
	while (print)
	{
		printf("%s\n", print);
		free (print);
		print = get_next_line(read_fd);				
	}
	free (print);
	close (read_fd);
	close (write_fd);
	write (2, "ICI\n", 4);
	return (write(2, "Execve Error\n", 13), -1);
}
