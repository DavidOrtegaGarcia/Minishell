/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:53:31 by daortega          #+#    #+#             */
/*   Updated: 2023/10/06 20:12:42 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sfinal;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	sfinal = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (sfinal == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		sfinal[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
		sfinal[i++] = s2[j++];
	sfinal[i] = '\0';
	return (sfinal);
}
