/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marberge <marberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:07:52 by marberge          #+#    #+#             */
/*   Updated: 2025/12/11 16:06:39 by marberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = ft_strlen(s);
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char const *s2)
{
    char    *res;
    size_t  len1;
    size_t  len2;
    int     i;
    int     j;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    res = malloc((len1 + len2 + 1) * sizeof(char));
    if (!res)
    {
        free(s1);
        return (NULL);
    }
    i = -1;
    while (++i < (int)len1)
        res[i] = s1[i];
    j = 0;
    while (j < (int)len2)
    {
        res[i++] = s2[j++]; 
    }
    res[i] = '\0';
    free(s1);
    return (res);
}

char	*ft_trim_from_start(char *str)
{
	int		i;
	int		k;
	char	*res;

	if (!str || str[0] == '\0')
		return (NULL);
	i = ft_search_char(str);
	if (i > -1)
		i = i + 1;
	else
		i = ft_strlen(str); 
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	k = 0;
	while (k < i)
	{
		res[k] = str[k];
		k++;
	}
	res[k] = '\0';
	return (res);
}
