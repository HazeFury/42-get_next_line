/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:34:46 by marberge          #+#    #+#             */
/*   Updated: 2025/12/02 12:49:43 by marberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_search_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
			printf("X");
		else
			printf("%c", str[i]);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	static char	buf[BUFFER_SIZE];
	int			nb_read;
	int			i;

	stash = NULL;
	i = 0;
	while (i < 10)
	{
		buf[i] = '\0';
		i++;
	}
	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
			return (NULL);
		if (nb_read < BUFFER_SIZE)
			buf[nb_read] = '\0';
		ft_search_char(buf);
	}
	return (stash);
}

int	main(void)
{
	int		fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	get_next_line(fd);
	close(fd);
	return (0);
}
