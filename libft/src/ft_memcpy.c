/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:19:48 by aalliot           #+#    #+#             */
/*   Updated: 2014/11/05 16:29:23 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*strdst;
	const unsigned char	*strsrc;

	strdst = (unsigned char*)dst;
	strsrc = (const unsigned char*)src;
	while (n--)
		*strdst++ = *strsrc++;
	return (dst);
}
