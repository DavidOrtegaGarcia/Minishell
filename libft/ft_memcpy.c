/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:07 by daortega          #+#    #+#             */
/*   Updated: 2023/09/25 15:19:59 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*sdst;
	const char	*ssrc;

	sdst = dst;
	ssrc = src;
	i = 0;
	if (dst != NULL || src != NULL)
	{
		while (i < n)
		{
			sdst[i] = ssrc[i];
			i++;
		}
	}
	return (sdst);
}
