/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:51:05 by daortega          #+#    #+#             */
/*   Updated: 2023/09/27 17:05:28 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;
	size_t	dst_length;
	size_t	i;
	size_t	result;

	dst_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	i = 0;
	result = 0;
	if (dstsize <= dst_length)
		result = src_length + dstsize;
	if (dstsize > dst_length)
		result = src_length + dst_length;
	if (dstsize != 0 && dst_length < dstsize)
	{
		while (src[i] != '\0' && dst_length < (dstsize - 1))
		{
			dst[dst_length] = src[i];
			dst_length++;
			i++;
		}
		dst[dst_length] = '\0';
	}
	return (result);
}
