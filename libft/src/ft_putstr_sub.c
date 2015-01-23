/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 15:10:45 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/02 15:10:57 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_sub(char *str, int start, int l)
{
	if (!str)
		return ;
	str += start;
	while (l-- && *str)
	{
		ft_putchar(*str++);
	}
}
