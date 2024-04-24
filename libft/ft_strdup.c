/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:40:23 by daortega          #+#    #+#             */
/*   Updated: 2024/02/23 15:19:16 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	s1_length;
	size_t	i;

	i = 0;
	s1_length = ft_strlen(s1) + 1;
	str = (char *) malloc(s1_length * sizeof(char));
	if (str == NULL)
		return (0);
	while (i < s1_length)
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}
