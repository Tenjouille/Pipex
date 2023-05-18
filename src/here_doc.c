/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:47:13 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/17 16:40:59 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"



int init_here_doc(int *pipe_fd, char *av, char **env)
{
	char	*buff;
	
	close (pipe_fd);
	buff = get_next_line(0);
	while (ft_strcmp(buff, av[2]))
	{
		//stock qque part tous les gnl(0);
		free(buff);
		buff = get_next_line(0);
	}
	
}

int ft_here_doc(int ac, char **av, char **env)
{
	int		j;
	int		pipe_fd[2];
	int		fd_outfile;
	int		status;
	pid_t	pid;
	
	if (init_here_doc(pipe_fd, av, env))
		return (0);
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
				write(2, "Last Process\n", 13);
				fd_outfile = open(av[ac - 1], O_RDWR | O_CREAT, 0644);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
				if (ft_child_process(fd_infile, fd_outfile, av[ac - 2], env) == -1)
					return (write(2, "Error in last child\n", 20), 0);
			}
			else
			{
				close(pipe_fd[0]);
				write(2, "First Process\n", 14);
				if (ft_child_process(fd_infile, pipe_fd[1], av[j], env) == -1)
					return (write(2, "Error in first child\n", 21), 0);
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
	return (0);
}