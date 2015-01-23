/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 17:18:41 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/16 17:18:47 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void			ft_merge(int *tab, int bgg1, int end1, int end2)
{
	int			*tab1;
	int			bgg2;
	int			cnt1;
	int			cnt2;
	int			i;

	bgg2 = end1 + 1;
	cnt1 = bgg1;
	cnt2 = bgg2;
	tab1 = (int*)malloc(sizeof(int) * (end1 - bgg1 + 1));
	i = bgg1 - 1;
	while (i++ <= end1)
		tab1[i - bgg1] = tab[i];
	i = bgg1 - 1;
	while (i++ <= end2 && cnt1 != bgg2)
	{
		if (cnt2 == (end2 + 1))
			tab[i] = tab1[cnt1++ - bgg1];
		else if (tab1[cnt1 - bgg1] < tab[cnt2])
			tab[i] = tab1[cnt1++ - bgg1];
		else
			tab[i] = tab[cnt2++];
	}
	free(tab1);
}

void			ft_merge_sort_rec(int *tab, int bgg, int end)
{
	int			mid;

	if (bgg != end)
	{
		mid = (bgg + end) / 2;
		ft_merge_sort_rec(tab, bgg, mid);
		ft_merge_sort_rec(tab, mid + 1, end);
		ft_merge(tab, bgg, mid, end);
	}
}

void			ft_sort_mrg(int *tab, int lgt)
{
	if (lgt <= 0)
		return ;
	else
		ft_merge_sort_rec(tab, 0, lgt - 1);
}
