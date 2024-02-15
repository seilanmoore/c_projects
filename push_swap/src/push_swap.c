/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:22:59 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/15 14:51:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int argc, char	**argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	argc--;
	if (argc == 1)
		argc = split_arg(&stack_a, argv[1]);
	else if (argc > 1)
		argc = arr_to_lst(argc, argv, &stack_a, 0);
	if (!argc)
		return (-1);
	if (sorted(stack_a))
		return (lst_clear(&stack_a), 0);
	if (argc < 12)
		sort_few(&stack_a, &stack_b);
	else
	{
		divide(&stack_a, &stack_b);
		while (stack_b)
			to_top(&stack_a, &stack_b);
		last_sort(&stack_a);
	}
	return (lst_clear(&stack_a), lst_clear(&stack_b), 0);
}
