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
 * Converts a string to a double (ASCII to float)
 * 
 * This function converts a string representation of a floating-point number
 * to its double equivalent. It handles:
 * - Positive and negative numbers
 * - Decimal points
 * - Leading and trailing whitespace
 * - Invalid characters (stops parsing at first invalid char)
 * 
 * Parameters:
 * - str: pointer to the string to convert
 * 
 * Returns:
 * - double: the converted floating-point number
 * - 0.0: if the string is invalid or empty
 * 
 * Examples:
 * - ft_atof("3.14") returns 3.14
 * - ft_atof("-0.5") returns -0.5
 * - ft_atof("123.456") returns 123.456
 * - ft_atof("42") returns 42.0
 * - ft_atof("invalid") returns 0.0
 */
double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	power;
	int		i;

	if (!str)
		return (0.0);
	result = 0.0;
	sign = 1.0;
	i = 0;
	// Skip whitespace
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
		   str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	// Handle sign
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	// Parse integer part
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	// Parse decimal part
	if (str[i] == '.')
	{
		i++;
		power = 1.0;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10.0 + (str[i] - '0');
			power *= 10.0;
			i++;
		}
		result /= power;
	}
	return (sign * result);
}
