/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:05:21 by dmontana          #+#    #+#             */
/*   Updated: 2024/11/27 13:26:37 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//------------------------------------------------------------------------
//i++: we need len of the string (i) + one (null terminator character)
//i--: same logic, removes the null for copying the string characters
//------------------------------------------------------------------------
//Truth and False in C: false == zero, true == any other value.
//------------------------------------------------------------------------
//Truth and False in Python: false == None, empty objects and keyword False
//true instead is all the rest, all non empty objects and keywork True
//------------------------------------------------------------------------

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ptr;
	int		i;

	i = 0;
	while (src[i])
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
