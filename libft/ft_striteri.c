/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:08:13 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/01 15:08:15 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Writing s + i gives you the pointer to the character at position i in s.
// It's equivalent to writing &s[i].
//WHY? Remember pointer arithmetic, pointer +- i = pointer moved i positions. 

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}
