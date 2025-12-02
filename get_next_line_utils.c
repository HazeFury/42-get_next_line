/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:07:52 by marberge          #+#    #+#             */
/*   Updated: 2025/12/02 18:48:18 by marberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*res;
	int		i;
	int		k;

	i = 0;
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	k = 0;
	while (s2[k] != '\0')
	{
		res[i] = s2[k];
		i++;
		k++;
	}
	free(s1);
	res[i] = '\0';
	return (res);
}

char	*ft_trim_from_start(char *str)
{
	int		i;
	int		k;
	char	*res;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	k = 0;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (k < i + 1)
	{
		res[k] = str[k];
		k++;
	}
	res[k] = '\0';
	free(str);
	return (res);
}
