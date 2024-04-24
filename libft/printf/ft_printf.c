/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:01:57 by daortega          #+#    #+#             */
/*   Updated: 2023/12/13 18:16:14 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	static	check_format(char const c, va_list args)
{
	int	contador;

	contador = 0;
	if (c == 'c')
		contador = ft_putchar(va_arg(args, int));
	else if (c == 's')
		contador = ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		contador = ft_putpointer(va_arg(args, unsigned long));
	else if (c == 'd')
		contador = ft_putnum(va_arg(args, int));
	else if (c == 'i')
		contador = ft_putnum(va_arg(args, int));
	else if (c == 'u')
		contador = ft_putunsnum(va_arg(args, unsigned int));
	else if (c == 'x')
		contador = ft_puthexalow(va_arg(args, unsigned int));
	else if (c == 'X')
		contador = ft_puthexaup(va_arg(args, unsigned int));
	else if (c == '%')
		contador = ft_putchar(c);
	return (contador);
}

int	static	print_str(char const *str, va_list	args)
{
	int		result;
	int		aux;
	int		i;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			aux = check_format(str[++i], args);
			if (aux == -1)
				return (-1);
			result += aux;
			aux = 0;
			i++;
		}
		else
		{
			if (ft_putchar(str[i++]) == -1)
				return (-1);
			result++;
		}
	}
	return (result);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		result;

	va_start(args, str);
	result = 0;
	if (str == NULL)
		return (0);
	result = print_str(str, args);
	va_end(args);
	return (result);
}
