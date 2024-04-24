/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:00:16 by daortega          #+#    #+#             */
/*   Updated: 2023/09/26 15:25:09 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	int					result;

	result = 0;
	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && i < n && result == 0)
	{
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	if ((s1[i] != '\0' || s2[i] != '\0') && i < n && result == 0)
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (result > 0)
		result = 1;
	else if (result < 0)
		result = -1;
	return (result);
}
