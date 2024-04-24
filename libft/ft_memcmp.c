/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:40:21 by daortega          #+#    #+#             */
/*   Updated: 2023/09/25 16:05:22 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	int						result;
	const unsigned char		*ss1;
	const unsigned char		*ss2;

	i = 0;
	result = 0;
	ss1 = s1;
	ss2 = s2;
	while (i < n && result == 0)
	{
		if (ss1[i] != ss2[i])
			result = ss1[i] - ss2[i];
		i++;
	}
	return (result);
}
