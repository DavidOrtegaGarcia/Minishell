/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:38:59 by daortega          #+#    #+#             */
/*   Updated: 2023/12/13 19:21:34 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

int	ft_gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (0);
}

char	*ft_gnl_strdup(char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((ft_gnl_strlen(s1) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*sfinal;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	sfinal = malloc((ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1) * sizeof(char));
	if (sfinal == NULL)
		return (free(s1), NULL);
	while (s1[i] != '\0')
	{
		sfinal[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		sfinal[i++] = s2[j++];
	sfinal[i] = '\0';
	free(s1);
	return (sfinal);
}
