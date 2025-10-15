/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:24:21 by dmontana          #+#    #+#             */
/*   Updated: 2025/01/03 13:24:23 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//NOTE: I pass a void (generic) pointer so that I can then use any
//data type for the value.

//STEP1: Allocate memory for the new node
//STEP2: Assign the value to the new node
//STEP3: Set the next pointer to NULL

//To access a value on the list it's head.content and if it's a pointer
//i need to use the arrow.

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head -> content = content;
	head -> next = NULL;
	return (head);
}
