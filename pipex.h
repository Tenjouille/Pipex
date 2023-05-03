/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:50:20 by tbourdea          #+#    #+#             */
/*   Updated: 2023/02/21 17:14:12 by tbourdea         ###   ########.fr       */
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

char	**ft_allpaths(char **env);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	**ft_split_w_slash(char const *s, char c);
char	*ft_sepwords(char **dest, char const *s, int c, int j);
char	*ft_sepwords_w_slash(char **dest, char const *s, int c, int j);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_freeall(char **dest, int j);
int		ft_strlen(char *str);
int		ft_mallocsize(char const *s, char c);
int		ft_child_process(int read_fd, int write_fd, char *av, char **env);

#endif