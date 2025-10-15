/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:31:12 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/04 13:42:48 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//memcpy does not check for overlapping memory areas. If src and dest overlap,
//the behavior of memcpy is undefined. In such cases, 
//memmove should be used instead, as it handles overlapping regions.

//NOTE: (char *)dest[i] IS NOT CORRECT, as I need to cast BEFORE accessing
//the i-th elementh of the pointer. I need to use ((char *)dest)[i]
//This way I'm sure that I'm first casting and then accessing the i-th elem.

#include "libft.h"

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
