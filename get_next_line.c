/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:34:46 by marberge          #+#    #+#             */
/*   Updated: 2025/12/02 16:25:01 by marberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_search_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	static char	*buffer;
	int			nb_read;
	unsigned int	i;

	stash = "";
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	nb_read = -1;
	while (nb_read != 0 && ft_search_char(stash) != 1)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
			return (NULL);
		if (nb_read < BUFFER_SIZE)
			buffer[nb_read] = '\0';
		// tmp = ft_search_char(buffer);
		stash = ft_strjoin(stash, buffer);
	}
	stash = ft_trim_from_start(stash);
	printf("\nstash = %s\n", stash + 0);
	return (stash);
}

int	main(void)
{
	int		fd;
	char	*test;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	test = get_next_line(fd);
	free(test);
	close(fd);
	return (0);
}
