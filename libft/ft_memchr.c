/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:08:53 by daortega          #+#    #+#             */
/*   Updated: 2023/09/27 13:38:23 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*ss;
	unsigned char			uc;

	i = 0;
	ss = s;
	uc = c;
	while (i < n)
	{
		if (ss[i] == uc)
			return ((void *)&ss[i]);
		i++;
	}
	return (0);
}
