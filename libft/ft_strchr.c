/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:47:56 by dmontana          #+#    #+#             */
/*   Updated: 2024/12/28 18:46:27 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//strchr searches for the first occurrence of a character in a string

//NOTE: iterate until c is found, if not return a pointer to
//end of string.
//NOTE: If c is a string terminator, return a pointer to that position.
//NOTE: if c not found, return NULL pointer.

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == *s)
		return ((char *)s);
	return (NULL);
}
