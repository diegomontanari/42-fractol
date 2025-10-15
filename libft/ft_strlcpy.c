/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:32:53 by dmontana          #+#    #+#             */
/*   Updated: 2024/12/28 17:26:39 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//REMEMBER: const means 'read only', so the value cannot be modified

//STEP1: copy first  dstsize - n1 bytes into dest,
//STEP2: adds null terminator after,
//STEP3: returns len of src (the string it tried to create).
//S3 helps you see if the string was  entirely copied.

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;
	size_t	index;

	index = 0;
	count = ft_strlen(src);
	if (size != 0)
	{
		while (src[index] != '\0' && index < (size - 1))
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (count);
}
