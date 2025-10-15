/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:40:33 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/04 14:33:22 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//like memcpy copies memory from src to dest, but prevents
//memory overlap in a super smart way.

//Memory is normally copied from first byte to last. This creates
//problems if scr is modified while copying.

/*
How to solve this? If the source memory is located BEFORE the destination
memory (i.e., the copy would go forward in memory), memmove will copy the 
memory in a FORWARD direction (like memcpy).

If the source memory is located AFTER the destination memory 
(i.e., the copy would go backward in memory), memmove will copy the memory
in REVERSE order, starting from the end and working backwards.
*/

//SOME GOOD CODING PRACTICES:
//NOTE1: I use a BUFF because it's easier to debug in more complex code
//NOTE2: In copy operations, using UNSIGNED is better as it avoids
//ambiguity (in some systems negatives are -n127, but in others up to n127
//is positive and from n128 to n255 is negative so....)

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	unsigned char	*str1_buff;
	unsigned char	*str2_buff;

	if (!str1 || !str2)
		return (NULL);
	str1_buff = (unsigned char *)str1;
	str2_buff = (unsigned char *)str2;
	if (str2 < str1)
		while (n--)
			str1_buff[n] = str2_buff[n];
	else
		while (n--)
			*str1_buff++ = *str2_buff++;
	return (str1);
}
