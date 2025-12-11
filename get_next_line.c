/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:34:46 by marberge          #+#    #+#             */
/*   Updated: 2025/12/11 16:02:42 by marberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_search_char(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_resize_stash(char *str)
{
	int		i;
	char	*new_stash;

	i = ft_search_char(str);
	if (i != -1)
	{
		new_stash = ft_strdup(str + (i + 1));
		if (!new_stash)
		{
			free(str);
			return (NULL);
		}
	}
	else
		new_stash = NULL;
	free(str);
	return (new_stash);	
}

// char	*get_next_line(int fd)
// {
// 	static char	*stash;
// 	char		*buffer;
// 	int			nb_read;
// 	char		*line;

// 	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buffer)
// 	{
// 		if (stash) 
//     	{
//         	free(stash); 
//         	stash = NULL;
// 		}
// 		return (NULL);
// 	}
// 	nb_read = 1;
// 	if ((ft_search_char(stash) == -1) && nb_read > 0)
// 	{
// 		while (nb_read > 0)
// 		{
// 			nb_read = read(fd, buffer, BUFFER_SIZE);

// 			if (nb_read == -1)
// 			{
// 				free(stash);
// 				stash = NULL;
// 				free(buffer);
// 				return (NULL);	
// 			}
// 			buffer[nb_read] = '\0';
// 			stash = ft_strjoin(stash, buffer);
// 			if (!stash)
// 			{
// 				free(buffer);
// 				return (NULL);
// 			}
// 			if (ft_search_char(buffer) != -1)
// 				break ;
// 		}
// 	}
// 	line = ft_trim_from_start(stash);
// 	if (!line)
// 	{
// 		free(stash);
// 		stash = NULL;
// 	}
// 	else
// 		stash = ft_resize_stash(stash);
// 	free (buffer);
// 	return (line);
// }

char    *get_next_line(int fd)
{
    static char *stash;
    char        *buffer;
    int         nb_read;
    char        *line;

    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
    {
        if (stash)
        {
            free(stash);
            stash = NULL;
        }
        return (NULL);
    }
    nb_read = 1;
    while (ft_search_char(stash) == -1 && nb_read > 0)
    {
        nb_read = read(fd, buffer, BUFFER_SIZE);
        if (nb_read == -1)
        {
            free(buffer);
            if (stash)
            {
                free(stash);
                stash = NULL;
            }
            return (NULL);
        }
        if (nb_read > 0)
        {
            buffer[nb_read] = '\0';
            stash = ft_strjoin(stash, buffer);
            if (!stash)
            {
                free(buffer);
                return (NULL);
            }
            if (ft_search_char(buffer) != -1)
                break ;
        }
    }
    free(buffer);
    line = ft_trim_from_start(stash);
    if (!line)
    {
        free(stash);
        stash = NULL;
    }
    else
        stash = ft_resize_stash(stash); // Nettoyage normal
    return (line);
}

int	main(void)
{
	int		fd;
	char	*test;
	int		i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	// while (i < 8)
	// {
	// 	test = get_next_line(fd);
	// 	printf("%s", test);
	// 	free(test);
	// 	i++;
	// }
	test = get_next_line(fd);
	printf("%s", test);
	free(test);
	close(fd);
	return (0);
}
