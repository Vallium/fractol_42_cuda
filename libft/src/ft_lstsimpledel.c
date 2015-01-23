/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsimpledel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 16:27:00 by aalliot           #+#    #+#             */
/*   Updated: 2014/11/16 16:28:56 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsimpledel(t_list **alst)
{
	if (*alst)
	{
		ft_lstsimpledel(&(*alst)->next);
		ft_lstsimpledelone(alst);
	}
}
