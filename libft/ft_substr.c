/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:05:00 by daortega          #+#    #+#             */
/*   Updated: 2023/09/29 17:47:27 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	subs_length;

	if (start >= ft_strlen(s))
		subs_length = 0;
	else if ((size_t) ft_strlen(&s[start]) < len)
		subs_length = (size_t) ft_strlen(&s[start]);
	else
		subs_length = len;
	subs = malloc((subs_length + 1) * sizeof(char));
	if (subs == NULL)
		return (0);
	i = 0;
	while (subs_length != 0 && i < len && s[start] != '\0')
		subs[i++] = s[start++];
	subs[i] = '\0';
	return (subs);
}
