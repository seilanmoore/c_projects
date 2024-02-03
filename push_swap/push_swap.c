/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:22:59 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/03 13:14:15 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_atol(const char *str)
{
	unsigned char	*ptr;
	long			sign;
	long			nbr;

	nbr = 0;
	sign = 1;
	ptr = (unsigned char *) str;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n'
		|| *ptr == '\v' || *ptr == '\f' || *ptr == '\r')
		ptr++;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign *= -1;
		ptr++;
	}
	if (*ptr == '+' || *ptr == '-')
		return (0);
	while (*ptr != '\0' && *ptr >= '0' && *ptr <= '9')
	{
		nbr = nbr * 10 + (*ptr - '0');
		ptr++;
	}
	nbr *= sign;
	return (nbr);
}



//pa (push a): Take the first element at the
//top of b and put it at the top of a.
//Do nothing if b is empty.

void	push_a(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;

	if (*stack_b)
	{
		tmp = (*stack_b)->next;
		if (!(*stack_a))
		{
			(*stack_a) = (*stack_b);
			(*stack_a)->next = NULL;
			(*stack_b) = tmp;
		}
		else
		{
			(*stack_b)->next = (*stack_a);
			(*stack_a) = (*stack_b);
			(*stack_b) = tmp;
		}
		printf("pa\n");
	}
}

//pb (push b): Take the first element at the
//top of a and put it at the top of b.
//Do nothing if a is empty.

void	push_b(t_stack **stack_b, t_stack **stack_a)
{
	t_stack	*tmp;

	if (*stack_a)
	{
		tmp = (*stack_a)->next;
		if (!(*stack_b))
		{
			(*stack_b) = (*stack_a);
			(*stack_b)->next = NULL;
			(*stack_a) = tmp;
		}
		else
		{
			(*stack_a)->next = (*stack_b);
			(*stack_b) = (*stack_a);
			(*stack_a) = tmp;
		}
		printf("pb\n");
	}
}

//ra (rotate a): Shift up all elements of stack a by 1.
//The first element becomes the last one.

void	rotate_a(t_stack **stack_a, int a_b)
{
	t_stack	*tmp;
	t_stack	*first;
	t_stack	*last;

	if (*stack_a)
	{
		if ((*stack_a)->next)
		{
			first = *stack_a;
			*stack_a = first->next;
			first->next = NULL;
			last = lst_last(*stack_a);
			last->next = first;
			if (!a_b)
				printf("ra\n");
		}
	}
}

//rb (rotate b): Shift up all elements of stack b by 1.
//The first element becomes the last one.

void	rotate_b(t_stack **stack_b, int a_b)
{
	t_stack	*tmp;
	t_stack	*first;
	t_stack	*last;

	if (*stack_b)
	{
		if ((*stack_b)->next)
		{
			first = *stack_b;
			*stack_b = first->next;
			first->next = NULL;
			last = lst_last(*stack_b);
			last->next = first;
			if (!a_b)
				printf("rb\n");
		}
	}
}

//rr : ra and rb at the same time.

void	rotate_a_b(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a && *stack_b)
	{
		if ((*stack_a)->next && (*stack_b)->next)
		{
			rotate_a(&(*stack_a), 1);
			rotate_b(&(*stack_b), 1);
			printf("rr\n");
		}
	}
}

//rra (reverse rotate a): Shift down all elements of stack a by 1.
//The last element becomes the first one.

void	reverse_rotate_a(t_stack **stack_a, int a_b)
{
	t_stack	*tmp;
	t_stack	*first;
	t_stack	*last;

	if (*stack_a)
	{
		if ((*stack_a)->next)
		{
			first = *stack_a;
			tmp = *stack_a;
			*stack_a = lst_last(*stack_a);
			while ((tmp->next)->next)
			{
				if ((tmp->next)->next == *stack_a)
					(tmp->next)->next = NULL;
				else
					tmp = tmp->next;
			}
			if (*stack_a == first->next)
				first->next = NULL;
			(*stack_a)->next = first;
			if (!a_b)
				printf("rra\n");
		}
	}
}

//rrb (reverse rotate b): Shift down all elements of stack b by 1.
//The last element becomes the first one.

void	reverse_rotate_b(t_stack **stack_b, int a_b)
{
	t_stack	*tmp;
	t_stack	*first;
	t_stack	*last;

	if (*stack_b)
	{
		if ((*stack_b)->next)
		{
			first = *stack_b;
			tmp = *stack_b;
			*stack_b = lst_last(*stack_b);
			while ((tmp->next)->next)
			{
				if ((tmp->next)->next == *stack_b)
					(tmp->next)->next = NULL;
				else
					tmp = tmp->next;
			}
			if (*stack_b == first->next)
				first->next = NULL;
			(*stack_b)->next = first;
			if (!a_b)
				printf("rrb\n");
		}
	}
}

//rrr : rra and rrb at the same time.

void	reverse_rotate_a_b(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a && *stack_b)
	{
		if ((*stack_a)->next && (*stack_b)->next)
		{
			reverse_rotate_a(&(*stack_a), 1);
			reverse_rotate_b(&(*stack_b), 1);
			printf("rrr\n");
		}
	}
}

int	sorted(t_stack *stack_a)
{
	int	prev;

	if (!stack_a)
		return (0);
	prev = stack_a->index;
	while (stack_a->next)
	{
		if (prev > (stack_a->next)->index)
			return (0);
		stack_a = stack_a->next;
		prev = stack_a->index;
	}
	return (1);
}

t_stack	*get_min(t_stack *stack_a)
{
	t_stack	*min;
	t_stack	*tmp;

	if (!stack_a)
		return (write(1, "Error\n", 7), stack_a);
	tmp = stack_a;
	while (tmp)
	{
		if (tmp->index == -1)
			min = tmp;
		tmp = tmp->next;
	}
	while (stack_a)
	{
		if (min->number > stack_a->number && stack_a->index == -1)
			min = stack_a;
		stack_a = stack_a->next;
	}
	return (min);
}

void	index_stack(t_stack **stack_a)
{
	int		i;
	t_stack	*min;

	i = 0;
	min = get_min(*stack_a);
	while (i < lst_size(*stack_a))
	{
		min->index = i;
		min = get_min(*stack_a);
		i++;
	}
}

int	get_pos_max(t_stack *stack_b)
{
	int		pos;
	int		max;
	t_stack	*tmp;

	pos = 0;
	max = stack_b->index;
	tmp = stack_b;
	stack_b = stack_b->next;
	while (stack_b)
	{
		if (max < stack_b->index)
			max = stack_b->index;
		stack_b = stack_b->next;
	}
	while (tmp)
	{
		if (max == tmp->index)
			return (pos);
		tmp = tmp->next;
		pos++;
	}
}

void	push_max_a(t_stack	**stack_a, t_stack **stack_b)
{
	int	i;

	while (*stack_b)
	{
		i = get_pos_max(*stack_b);
		if (i == 1)
			swap_b(&(*stack_b), 0);
		else if (i > 1)
		{
			if (i <= (lst_size(*stack_b) / 2))
			{
				while (i-- > 0)
					rotate_b(&(*stack_b), 0);
			}
			else
			{
				i = lst_size(*stack_b) - i;
				while (i-- > 0)
					reverse_rotate_b(&(*stack_b), 0);
			}
		}
		push_a(&(*stack_a), &(*stack_b));
	}
}

//13 best number for 500, 7 for 100 

void	push_min_b(t_stack	**stack_b, t_stack	**stack_a)
{
	int	range;
	int	add;
	int	pushed;
	int	limit;

	range = (lst_size(*stack_a) - 1) / 13;
	add = range + 1;
	pushed = 0;
	limit = lst_size(*stack_a);
	while (lst_size(*stack_a) > 1)
	{
		while (pushed < range && pushed < limit)
		{
			if ((*stack_a)->index <= range)
			{
				push_b(&(*stack_b), &(*stack_a));
				pushed++;
			}
			else
				rotate_a(&(*stack_a), 0);
		}
		range += add;
	}
	push_b(&(*stack_b), &(*stack_a));
}

int	ft_error(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 2)
		return (1);
	if (argc < 3)
		return (printf("Error\n"), 1);
	while (++i < argc)
		if (ft_atol(argv[i]) == 0 && argv[i][0] != '0'
			|| (ft_atol(argv[i]) < -2147483648 || ft_atol(argv[i]) > 2147483647))
			return (printf("Error\n"), 1);
	i = 1;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (ft_atol(argv[i]) == ft_atol(argv[j]))
				return (printf("Error\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char	**argv)
{
	int		i;
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_stack	*tmp;

	if (ft_error(argc, argv))
		return (-1);
	stack_b = NULL;
	stack_a = new_node(atoi(argv[1]));
	if (!stack_a)
		return (-1);
	i = 1;
	while (++i < argc)
	{
		tmp = new_node(atoi(argv[i]));
		if (!tmp)
			return (lst_clear(&stack_a), -1);
		lst_add_back(&stack_a, tmp);
	}
	index_stack(&stack_a);
	if (sorted(stack_a))
		return (printf("Error\n"), 1);
	push_min_b(&stack_b, &stack_a);
	push_max_a(&stack_a, &stack_b);
	return (lst_clear(&stack_a), lst_clear(&stack_b), 0);
}
