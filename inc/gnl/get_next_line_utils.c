/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 04:05:08 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/12/07 04:07:53 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ftg_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ftg_strjoin(char *s1, char *s2)
{
	char	*p;
	int		len2;
	int		i;
	int		len1;

	len1 = ftg_strlen(s1);
	len2 = ftg_strlen(s2);
	p = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i++ < len1)
		p[i - 1] = s1[i - 1];
	while (i++ < len1 + len2 + 1)
		p[i - 2] = s2[i - len1 - 2];
	p[len1 + len2] = '\0';
	free(s1);
	return (p);
}

char	*ftg_strdup(char *s)
{
	int		i;
	int		len;
	char	*buff;

	i = 0;
	len = ftg_strlen(s);
	buff = malloc(sizeof(char) * len + 1);
	if (!buff)
		return (0);
	while (s[i])
	{
		buff[i] = s[i];
		i++;
	}
	buff[i] = '\0';
	free(s);
	return (buff);
}

char	*ftg_substr(char	*s, int start, int len)
{
	int		i;
	char	*str;
	int		size;

	i = 0;
	size = len;
	if (!s)
		return (NULL);
	if (start > ftg_strlen((char *)s) || s[0] == '\0')
		return (ftg_strdup(""));
	if (len > ftg_strlen(s))
		size = ftg_strlen(s) - start + 1;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
