/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:34:46 by marberge          #+#    #+#             */
/*   Updated: 2025/12/02 11:27:51 by marberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[10];
	int		nb_read;

	nb_read = 0;
	while (nb_read < 10)
	{
		buf[nb_read] = '\0';
		nb_read++;
	}
	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buf, 10);
		if (nb_read == -1)
			return (NULL);
		buf[nb_read] = '\0';
		printf("%s", buf);
	}
	return (buf);
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
