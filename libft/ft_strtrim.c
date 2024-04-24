/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:23:28 by daortega          #+#    #+#             */
/*   Updated: 2023/10/06 14:23:27 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	static	check_char(char c, char const *set)
{
	int	i;
	int	result;

	i = 0;
	result = -1;
	while (set[i] != '\0' && result == -1)
	{
		if (set[i] == c)
			result = 1;
		i++;
	}
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*sfinal;	
	int		pos_ini;
	int		pos_final;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	pos_ini = 0;
	pos_final = ft_strlen(s1);
	while (pos_ini < pos_final && check_char(s1[pos_ini], set) == 1)
		pos_ini++;
	while (pos_final > pos_ini && check_char(s1[pos_final - 1], set) == 1)
		pos_final--;
	sfinal = malloc((pos_final - pos_ini + 1) * sizeof(char));
	if (sfinal == NULL)
		return (NULL);
	while (pos_ini <= pos_final - 1)
		sfinal[i++] = s1[pos_ini++];
	sfinal[i] = '\0';
	return (sfinal);
}
