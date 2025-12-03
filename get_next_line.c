/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:34:46 by marberge          #+#    #+#             */
/*   Updated: 2025/12/03 20:07:17 by marberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_search_char(char *str)
{
	int	i;

	i = 0;
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
	// printf("longeur du reste : %zu\n", ft_strlen(str + (i + 1)));
	if (ft_strlen(str + (i + 1)) > 0)
		new_stash = ft_strdup(str + (i + 1));
	else
		new_stash = NULL;
	// printf("new stash : '%s'\n", new_stash);
	free(str);
	return (new_stash);	
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			nb_read;
	char		*line;

	if (!fd || fd == -1)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	nb_read = 1;
	while ((ft_search_char(stash) == -1) && nb_read > 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read <= 0)
			break ;
		buffer[nb_read] = '\0';
		// printf("buffer : '%s'\n", buffer);
		stash = ft_strjoin(stash, buffer);
	}
	line = ft_trim_from_start(stash);
	stash = ft_resize_stash(stash);
	// printf("=>  line : '%s'", line);
	// printf("=> stash : '%s'\n", stash);

	free(buffer);
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
	while (i < 8)
	{
		test = get_next_line(fd);
		printf("%s", test);
		free(test);
		i++;
	}
	close(fd);
	return (0);
}
