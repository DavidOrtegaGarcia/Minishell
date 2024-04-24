/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:55:37 by daortega          #+#    #+#             */
/*   Updated: 2023/12/13 18:28:54 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	static	get_num_digits_hexa(unsigned long n)
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
	return (n_digits + 2);
}

char	*hexaltoa(unsigned long n, char *basehexa)
{
	char			*result;
	int				n_digits;
	unsigned long	num;

	n_digits = get_num_digits_hexa(n);
	num = n;
	result = (char *) malloc((n_digits + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[n_digits--] = '\0';
	while (n_digits > 2)
	{
		result[n_digits--] = basehexa[(num % 16)];
		num /= 16;
	}
	result[2] = basehexa[(num % 16)];
	result[1] = 'x';
	result[0] = '0';
	return (result);
}

int	ft_putpointer(unsigned long address)
{
	char	*str;
	int		result;

	str = hexaltoa(address, "0123456789abcdef");
	if (str == NULL)
		return (-1);
	result = write(1, str, ft_strlen(str));
	free(str);
	return (result);
}
