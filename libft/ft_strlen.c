/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:03:04 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/04 18:12:44 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//size_t is largely used for measures, it is useful as:
//n1) It's not negative
//n2) Has generally more bytes than int

#include "libft.h"

int	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}
