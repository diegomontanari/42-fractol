/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:08:20 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/04 18:38:28 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//memset fills the first len bytes of memory pointed to by b with the value c, 
//starting from the end. Returns b.

//*b: pointer to block of memory to fill, (cannot be a char *b as we need to be 
//general and accept all pointers)

//Rembember: *function_name means it returns a pointer

//[n - one] starts from the last byte of len, this is useful as I do not need
//to create the variable i and put while (i < len)

//I initialize the pointer to NULL 

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buff;

	buff = (unsigned char *)b;
	while (len--)
		*buff++ = (unsigned char)c;
	return (b);
}
