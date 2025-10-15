/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:22:47 by dmontana          #+#    #+#             */
/*   Updated: 2024/12/28 15:28:02 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// STEP1: if True, return converted value
// STEP2: if False, return input value

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
