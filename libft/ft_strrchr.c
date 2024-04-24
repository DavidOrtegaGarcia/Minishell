/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:23:03 by daortega          #+#    #+#             */
/*   Updated: 2023/09/25 13:43:43 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	result;

	result = -1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			result = i;
		i++;
	}
	if (result != -1)
		return ((char *)&s[result]);
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (0);
}
