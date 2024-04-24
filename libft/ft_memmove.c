/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:27:55 by daortega          #+#    #+#             */
/*   Updated: 2023/09/25 13:26:32 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*sdst;
	const char	*ssrc;

	sdst = (char *)dst;
	ssrc = (char *)src;
	i = -1;
	if (dst != NULL || src != NULL)
	{
		if (dst > src)
		{
			while (len > 0)
			{
				sdst[len -1] = ssrc[len -1];
				len--;
			}
		}
		else
		{
			while (++i < len)
				sdst[i] = ssrc[i];
		}
	}
	return (sdst);
}
