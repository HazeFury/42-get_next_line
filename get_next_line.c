/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:34:46 by marberge          #+#    #+#             */
/*   Updated: 2025/12/12 15:04:36 by marberge         ###   ########.fr       */
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

void	ft_resize_stash(char *tmp, char *stash)
{
	int	i;
	int	k;

	k = 0;
	i = ft_search_char(tmp);
	if (i != -1)
	{
		i++;
		while (k < BUFFER_SIZE)
		{
			if (tmp[i] != '\0')
			{
				stash[k] = tmp[i];
				i++;
			}
			else
				stash[k] = '\0';
			k++;
		}
	}
	else
		ft_bzero(stash, BUFFER_SIZE + 1);
	free(tmp);
	return ;
}

char	*read_buffer_loop(int fd, char *stash, char *tmp, char *buffer)
{
	int				nb_read;

	nb_read = 1;
	while (ft_search_char(tmp) == -1 && nb_read > 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
		{
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
			ft_bzero(stash, BUFFER_SIZE + 1);
			return (NULL);
		}
		if (nb_read > 0)
		{
			buffer[nb_read] = '\0';
			tmp = ft_strjoin(tmp, buffer);
			if (!tmp)
				return (NULL);
			if (ft_search_char(buffer) != -1)
				return (tmp);
		}
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char		stash[BUFFER_SIZE + 1];
	char			*tmp;
	char			*buffer;
	char			*line;

	tmp = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (ft_strlen(stash) > 0)
		tmp = ft_strjoin(tmp, stash);
	tmp = read_buffer_loop(fd, stash, tmp, buffer);
	free(buffer);
	if (!tmp)
		return (NULL);
	line = ft_trim_from_start(tmp);
	if (!line)
	{
		free(tmp);
		tmp = NULL;
	}
	else
		ft_resize_stash(tmp, stash);
	return (line);
}

/* int main(void)
{
	int fd;
	char *test;
	int i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	while (i < 8)
	{
		test = get_next_line(fd);
		printf("%s", test);
		free(test);
		i++;
	}
	// test = get_next_line(fd);
	// printf("%s", test);
	// free(test);
	close(fd);
	return (0);
} */
