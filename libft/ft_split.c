/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:06:36 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/01 15:07:09 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NOTE: WHAT IS STATIC? WHY USING IT?

- It's a modifier that makes the function invisible to other files.
- FORMAL DEFINITION: a function that  has its scope limited to the file 
  in which it is declared.
- A static function is a good programming practice for several reasons:
- 1) NAMESPACE PROTECTION: in a project with many fille, it's easy that two
     funtions have the same name. This fixes the problem (2 equal names is ok)
- 2) OPTIMIZATION: compilers optimize better static functions

- The opposite of a static function is a public interface.
*/

#include "libft.h"

static size_t	get_word(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	ret = malloc(sizeof(char *) * (get_word(s, c) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			ret[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	ret[i] = 0;
	return (ret);
}
