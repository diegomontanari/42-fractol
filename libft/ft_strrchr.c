/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:47:02 by dmontana          #+#    #+#             */
/*   Updated: 2024/12/28 19:33:03 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// searches for the last occurrence of a char

// STEP1: iterate backwards until char is found
// STEP2: if (c == str. terminating char) condition not necessary.
// STEP3: if char not found return NULL

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i--;
	}
	return (NULL);
}
