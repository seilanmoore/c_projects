/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:53:03 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:02:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		if (*lst)
			ft_lstlast(*lst)->next = new;
		else
			*lst = new;
	}
}
