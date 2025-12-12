/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:04:46 by marberge          #+#    #+#             */
/*   Updated: 2025/12/12 17:34:37 by marberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_trim_from_start(char *str);
void	ft_bzero(void *s, size_t n);
int		ft_search_char(char *str);
void	ft_resize_stash(char *tmp, char *stash);
size_t	ft_strlen(const char *s);
char	*ft_read_buffer_loop(int fd, char *stash, char *tmp, char *buffer);
void	ft_set_null_and_free(char *str_to_free);

#endif
