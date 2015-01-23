/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_q_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 12:17:19 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/16 20:45:20 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			sort(void **tab, int bg, int ed, int (*f)(void *, void *))
{
	void		*pvt;
	int			lft;
	int			rgt;

	pvt = tab[bg];
	lft = bg - 1;
	rgt = ed + 1;
	if (bg >= ed)
		return ;
	while (1)
	{
		while (f(tab[--rgt], pvt) > 0)
			;
		while (f(tab[++lft], pvt) < 0)
			;
		if (lft < rgt)
			ft_swap(&tab[lft], &tab[rgt]);
		else
			break ;
	}
	sort(tab, bg, rgt, f);
	sort(tab, rgt + 1, ed, f);
}

void			ft_sort_qck(void **tab, int size, int (*f)(void *, void *))
{
	sort(tab, 0, size - 1, f);
}
