/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:58:46 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/20 15:06:20 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

void	ft_closeall(int fd1, int fd2, int fd3, int fd4)
{
	if (fd4 != fd3)
		close (fd4);
	if (fd3 != fd2)
		close (fd3);
	if (fd2 != fd1)
		close (fd2);
	close (fd1);
}

int	ft_parsing(pid_t pid, int ac)
{
	if (ac < 5)
	{
		ft_putstr_fd("Error, enter 2 filenames and at least 2 commandes.\n", 2);
		return (1);
	}
	if (pid == -1)
		return (write(2, "Fork Error\n", 11), 1);
	return (0);
}

int	ft_redirection(t_fd *fd, int j, char **av, char **env)
{
	if (!av[j + 2])
	{
		if (fd->outfile < 0)
			return (1);
		ft_closeall(fd->pipe[0], fd->pipe[1], fd->pipe[1], fd->pipe[1]);
		if (ft_child_process(fd->infile, fd->outfile, av[j], env) < 0)
			return (127);
	}
	else if (j == 2)
	{
		if (fd->infile < 0)
			return (1);
		ft_closeall(fd->pipe[0], fd->outfile, fd->outfile, fd->outfile);
		if (ft_child_process(fd->infile, fd->pipe[1], av[j], env) == -1)
			return (127);
	}
	else
	{
		ft_closeall(fd->pipe[0], fd->outfile, fd->outfile, fd->outfile);
		if (ft_child_process(fd->infile, fd->pipe[1], av[j], env) == -1)
			return (127);
	}
	return (0);
}

int	ft_parent_process(t_fd *fd, int j)
{
	ft_closeall(fd->pipe[1], fd->infile, fd->infile, fd->infile);
	fd->infile = fd->pipe[0];
	j++;
	return (j);
}

int	main(int ac, char **av, char **env)
{
	int		j;
	t_fd	fd;
	pid_t	pid;
	int		status;

	if (ac < 5)
		return (write(2, "Error\n", 6), 1);
	fd.infile = open(av[1], O_RDONLY);
	fd.outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	j = 2;
	while (j < ac - 1)
	{
		pipe(fd.pipe);
		pid = fork();
		if (pid == -1)
			return (write(2, "Fork Error\n", 11), 1);
		if (pid == 0)
			return (ft_redirection(&fd, j, av, env));
		else
			j = ft_parent_process(&fd, j);
	}
	ft_closeall(fd.pipe[0], fd.outfile, fd.infile, fd.infile);
	wait (&status);
	wait (&status);
	return (WEXITSTATUS(status));
}
