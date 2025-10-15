/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:22:18 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/04 13:03:04 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ft_memset(s, zero, n); just calls memset to substitute n bytes with zero

#include "libft.h"

void	ft_bzero(void *p, size_t n)
{
	ft_memset(p, 0, n);
}
