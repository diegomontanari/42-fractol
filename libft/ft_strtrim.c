/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:04:44 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/01 15:05:53 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// STEP1: skip until the first character that is not in set
// STEP2: set j to the last char of s1,
//than go back until the first character that is not in set
// Now I will have a string without set in front and back
// STEP3: malloc a new string with the size of j - i
//+ n_2 (difference between j and i + n_1 for the null terminator)

// WHY +n_2?? Think about it,
//to go from num_3 to num_7 the difference is num_4 even if the total number 
//of elements is num_5.
// This is because the subtraction only takes into account one limit...
// So, to include that one limit i need to do plus one (simply,
//to include both limits)

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	str = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!str)
		return (NULL);
	while (i <= j)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}
