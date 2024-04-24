/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:04:02 by daortega          #+#    #+#             */
/*   Updated: 2023/12/13 16:41:08 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	static	get_n_digits_hexa(unsigned int n)
{
	int	n_digits;

	n_digits = 0;
	if (n == 0)
		n_digits++;
	while (n != 0)
	{
		n /= 16;
		n_digits++;
	}
	return (n_digits);
}

char static	*hexaitoa(unsigned int n, char *basehexa)
{
	char	*result;
	int		n_digits;
	long	num;

	n_digits = get_n_digits_hexa(n);
	num = (long)n;
	result = (char *) malloc((n_digits + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[n_digits--] = '\0';
	while (n_digits > 0)
	{
		result[n_digits--] = basehexa[(num % 16)];
		num /= 16;
	}
	result[0] = basehexa[(num % 16)];
	return (result);
}

int	ft_puthexalow(unsigned int num)
{
	char	*str;
	int		result;

	str = hexaitoa(num, "0123456789abcdef");
	if (str == NULL)
		return (-1);
	result = write(1, str, ft_strlen(str));
	free(str);
	return (result);
}

int	ft_puthexaup(unsigned int num)
{
	char	*str;
	int		result;

	str = hexaitoa(num, "0123456789ABCDEF");
	if (str == NULL)
		return (-1);
	result = write(1, str, ft_strlen(str));
	free(str);
	return (result);
}
