/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:23:59 by daortega          #+#    #+#             */
/*   Updated: 2024/07/15 17:25:44 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && result == 0)
	{
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	if ((s1[i] != '\0' || s2[i] != '\0') && result == 0)
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (result > 0)
		result = 1;
	else if (result < 0)
		result = -1;
	return (result);
}