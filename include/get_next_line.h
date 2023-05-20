/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:02:58 by tbourdea          #+#    #+#             */
/*   Updated: 2023/05/20 14:39:02 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
/*				get_next_line.c				*/
char	*get_next_line(int fd);
char	*ft_newline(char *arch, int size);
char	*ft_row(char *arch);
char	*ft_strjoin(char *s1, char *s2, char sep);
/*				get_next_line_utils				*/
int		ft_gotcha(char *arch);
int		ft_strlen(char *str);
char	*ft_empty_str(int len);
#endif