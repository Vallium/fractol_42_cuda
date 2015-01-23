/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 13:45:14 by aalliot           #+#    #+#             */
/*   Updated: 2014/11/06 15:36:11 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			*ft_memalloc(size_t size)
{
	void		*ptr;

	ptr = (void*)malloc(sizeof(void) * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	return ((void*)ptr);
}
