/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 16:51:09 by aalliot           #+#    #+#             */
/*   Updated: 2014/11/07 13:38:24 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			*ft_strmap(const char *s, char (*f)(char))
{
	char		*ret;
	char		*str;

	if (s && f)
	{
		str = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
		if (!str)
			return (NULL);
		ret = str;
		while (*s && f && s)
		{
			*str = (*f)(*s);
			str++;
			s++;
		}
		*str = 0;
		return (ret);
	}
	return (NULL);
}
