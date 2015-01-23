/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:56:34 by aalliot           #+#    #+#             */
/*   Updated: 2014/11/05 17:47:43 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*strdst;
	const unsigned char	*strsrc;
	unsigned char		car;

	strdst = (unsigned char*)dst;
	strsrc = (const unsigned char*)src;
	car = (unsigned char)c;
	while (n--)
	{
		if ((*strdst++ = *strsrc++) == car)
			return (strdst);
	}
	return (NULL);
}
