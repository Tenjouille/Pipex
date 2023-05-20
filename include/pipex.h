/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:50:20 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/20 15:07:17 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int	pipe[2];
}		t_fd;
/*					pipex.c					*/
void	ft_closeall(int fd1, int fd2, int fd3, int fd4);
int		ft_parsing(pid_t pid, int ac);
int		ft_parent_process(t_fd *fd, int j);
int		ft_redirection(t_fd *fd, int j, char **av, char **env);
/*				cmd_execution.c				*/
int		ft_child_process(int read_fd, int write_fd, char *av, char **env);
void	ft_manage_execve_errors(char **allpath, char **av_cmd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s);
char	**ft_allpaths(char **env);
/*					cmd_path.c				*/
void	ft_freeall(char **dest, int j);
int		ft_mallocsize(char const *s, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_sepwords(char **dest, char const *s, int c, int j);
char	**ft_split(char const *s, char c);
#endif