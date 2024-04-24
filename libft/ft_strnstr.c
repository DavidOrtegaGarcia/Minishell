/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:11 by daortega          #+#    #+#             */
/*   Updated: 2023/09/27 17:51:33 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		result;
	size_t		needle_length;

	i = 0;
	result = 0;
	needle_length = ft_strlen(needle);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			if (len - i < needle_length)
				result = -1;
			else
				result = ft_strncmp(&haystack[i], needle, needle_length);
			if (result == 0)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
