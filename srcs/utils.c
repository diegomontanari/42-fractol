/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:00:00 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/03 15:00:00 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
 * Converte una stringa in un double (ASCII a float).
 * Il primo while gestisce la parte intera e il secondo la parte decimale.
 *
 * Parametri:
 * - str: puntatore alla stringa da convertire
 *
 * Restituisce:
 * - double: il numero convertito
 * - 0.0: se la stringa è invalida o vuota
 */
static double	parse_integer(const char *str, int *i)
{
	double	result;

	result = 0.0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10.0 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

static double	parse_decimal(const char *str, int *i)
{
	double	result;
	double	power;

	result = 0.0;
	power = 1.0;
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			result = result * 10.0 + (str[*i] - '0');
			power *= 10.0;
			(*i)++;
		}
		result /= power;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	int		i;

	result = 0.0;
	sign = 1.0;
	i = 0;
	if (!str)
		return (0.0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	result = parse_integer(str, &i);
	result += parse_decimal(str, &i);
	return (sign * result);
}
