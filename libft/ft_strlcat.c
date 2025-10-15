/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:30:34 by dmontana          #+#    #+#             */
/*   Updated: 2024/12/28 17:37:40 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//NOTES: size is the buffer for the concatenated string
//NOTES: i + j + one is because if both counters are less than size we
//keep iterating. The +one is because we need to leave space for null-ter char

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
