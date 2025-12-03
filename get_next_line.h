/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:32:46 by marberge          #+#    #+#             */
/*   Updated: 2025/12/03 15:16:40 by marberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_trim_from_start(char *str);
char	*ft_strdup(const char *s);
int		ft_search_char(char *str);
char	*ft_resize_stash(char *str);
size_t	ft_strlen(const char *s);

#endif
