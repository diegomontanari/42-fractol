/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_callocnuovo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:55:40 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/04 14:55:46 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//The name is confusing, the only real difference between malloc and calloc:
//MALLOC: just allocates memory, not cleaning garbage memory.
//CALLOC: initializes to zero every cell, cleaning possible garbage.

/*
Original calloc checks for overflow in multiplication, but adding the check
in this function will make moulinette tester return an error. The check:
if (elem_num && size > SIZE_MAX / elem_num)
    return (NULL);

Both size and elem_num must be small enough to avoid overflow when multiplied,
as either can cause the product to exceed SIZE_MAX.
*/

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	total;

	if (n == 0 || size == 0)
		return (malloc(0));
	if (n > ((size_t)-1) / size)
		return (NULL);
	total = n * size;
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}
