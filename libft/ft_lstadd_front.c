/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:24:50 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/03 13:24:53 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INFORMATION:
// A single pointer can modify the value of the node it points to.
// But IF YOU WANT TO MODIFY THE POINTER ITSELF,
// you need to pass a double pointer.
// Modify the pointer itself means that YOU WANT TO POINT IT TO A DIFFERENT NODE
//(so diff. ADRESS).

// In this case, you want to point the head to the new node.

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
