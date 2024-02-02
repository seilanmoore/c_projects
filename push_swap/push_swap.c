/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:22:59 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/02 19:29:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

typedef struct	s_stack
{
	int				index;
	int				number;
	struct s_stack	*next;	
}				t_stack;

t_stack	*new_node(int number)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		return (NULL);
	new_node->index = -1;
	new_node->number = number;
	new_node->next = NULL;
	return (new_node);
}
t_stack	*lst_last(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void lst_add_back(t_stack **lst, t_stack *new)
{
	if (lst && new)
	{
		if (*lst)
			lst_last(*lst)->next = new;
		else
			*lst = new;
	}
}

void	lst_clear(t_stack **lst)
{
	t_stack	*current;
	t_stack	*next;

	if (*lst)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}

void lst_add_front(t_stack **lst, t_stack *new)
{
	if (!(*lst) && new)
	{
		*lst = new_node(new->number);
		return ;
	}
	else if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	lst_print(t_stack *lst_a, t_stack *lst_b)
{
	while (lst_a || lst_b)
	{
		if (lst_a && lst_b)
		{
			printf("	[%d]	[%d]	[%d]		[%d]\n", lst_a->number, lst_b->number, lst_a->index, lst_b->index);
			lst_a = lst_a->next;
			lst_b = lst_b->next;
		}
		else if (lst_b)
		{
			printf("		[%d]				[%d]\n", lst_b->number, lst_b->index);
			lst_b = lst_b->next;
		}
		else
		{
			printf("	[%d]		[%d]	\n", lst_a->number, lst_a->index);
			lst_a = lst_a->next;
		}
	}
	printf("	-----	-----	--------	--------\n");
	printf("	[A]	[B]	[INDEX_A]	[INDEX_B]\n");
}

int	lst_size(t_stack *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

//sa (swap a): Swap the first 2 elements at the top of stack a.
//Do nothing if there is only one or no elements.
void	swap_a(t_stack **stack_a, int a_b)
{
	t_stack	*first;
	t_stack	*second;
	t_stack *third;

	if (*stack_a)
	{
		if ((*stack_a)->next)
		{
			first = *stack_a;
			second = (*stack_a)->next;
			third = second->next;
			first->next = third;
			second->next = first;
			*stack_a = second;
			if (!a_b)
				printf("sa\n");
		}
	}
}

//sb (swap b): Swap the first 2 elements at the top of stack b.
//Do nothing if there is only one or no elements.

void	swap_b(t_stack **stack_b, int a_b)
{
	t_stack	*first;
	t_stack	*second;
	t_stack *third;

	if (*stack_b)
	{
		if ((*stack_b)->next)
		{
			first = *stack_b;
			second = (*stack_b)->next;
			third = second->next;
			first->next = third;
			second->next = first;
			*stack_b = second;
			if (!a_b)
				printf("sb\n");
		}
	}
}

//ss : sa and sb at the same time.

void	swap_a_b(t_stack **stack_a, t_stack **stack_b)
{
	if(*stack_a && *stack_b)
	{
		if ((*stack_a)->next && (*stack_b)->next)
		{
			swap_a(&(*stack_a), 1);
			swap_b(&(*stack_b), 1);
			printf("ss\n");
		}
	}
}

//pa (push a): Take the first element at the top of b and put it at the top of a.
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

//pb (push b): Take the first element at the top of a and put it at the top of b.
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

//Reverse the whole list

/* char	*rotate_a(t_stack **stack_a)
{
	t_stack	*tmp;

	if (*stack_a)
	{
		tmp = NULL;
		while (push_b(&tmp, &(*stack_a)))
			;
		*stack_a = tmp;
		return ("ra");
	}
	return (NULL);
} */

//The first one becomes the last one and vice versa

/* char	*rotate_a(t_stack **stack_a)
{
	t_stack	*tmp;
	t_stack *first;
	t_stack	*last;

	if (*stack_a)
	{
		first = *stack_a;
		*stack_a = first->next;
		tmp = *stack_a;
		first->next = NULL;
		last = lst_last(*stack_a);
		if (tmp->next)
		{
			while ((tmp->next)->next)
				tmp = tmp->next;
			tmp->next = first;
			last->next = *stack_a;
			*stack_a = last;
		}
		else
			tmp->next = first;
		return ("ra");
	}
	return (NULL);
} */

//ra (rotate a): Shift up all elements of stack a by 1.
//The first element becomes the last one.

void	rotate_a(t_stack **stack_a, int a_b)
{
	t_stack	*tmp;
	t_stack *first;
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

/* char	*rotate_b(t_stack **stack_b)
{
	t_stack	*tmp;

	if (*stack_b)
	{
		tmp = NULL;
		while (push_a(&tmp, &(*stack_b)))
			;
		*stack_b = tmp;
		return ("rb");
	}
	return (NULL);
} */

/* char	*rotate_b(t_stack **stack_b)
{
	t_stack	*tmp;
	t_stack *first;
	t_stack	*last;

	if (*stack_b)
	{
		first = *stack_b;
		*stack_b = first->next;
		tmp = *stack_b;
		first->next = NULL;
		last = lst_last(*stack_b);
		if (tmp->next)
		{
			while ((tmp->next)->next)
				tmp = tmp->next;
			tmp->next = first;
			last->next = *stack_b;
			*stack_b = last;
		}
		else
			tmp->next = first;
		return ("ra");
	}
	return (NULL);
} */

//rb (rotate b): Shift up all elements of stack b by 1.
//The first element becomes the last one.

void	rotate_b(t_stack **stack_b, int a_b)
{
	t_stack	*tmp;
	t_stack *first;
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
	t_stack *first;
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
	t_stack *first;
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
		return (write(1,"Error\n", 7), stack_a);
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

int	get_unit(int number, int step)
{
	while (--step > 0)
	{
		number /= 10;
	}
	return (number % 10);
}

int	get_pos_b(t_stack	*stack_b, int *dec, int step)
{
	int		i;
	int		unit;
	t_stack	*first;

	if (!stack_b)
		return (-1);
	unit = 9;
	first = stack_b;
	while (unit > -1)
	{
		i = 0;
		while (stack_b)
		{
			if (get_unit(stack_b->index, step) == *dec
				&& get_unit(stack_b->index, step - 1) == unit)
					return (i);
			stack_b = stack_b->next;
			i++;
		}
		stack_b = first;
		unit--;
	}
	return (-1);
}

int	get_pos_a(t_stack	*stack_a, int *dec, int step)
{
	int		i;
	int		unit;
	int		d;
	t_stack	*first;

	if (!stack_a)
		return (-1);
	unit = 0;
	d = 0;
	i = 0;
	first = stack_a;
	if (step == 3)
	{
		while (d <= 9)
		{
			unit = 0;
			while (unit <= 9)
			{
				i = 0;
				while (stack_a)
				{
					if (get_unit(stack_a->index, step) == *dec
						&& get_unit(stack_a->index, step - 1) == d
						&& get_unit(stack_a->index, step - 2) == unit)
							return (i);
					stack_a = stack_a->next;
					i++;
				}
				stack_a = first;
				unit++;
			}
			d++;
		}
	}
	else
	{
		while (stack_a)
		{
			if (get_unit(stack_a->index, step) == *dec)
					return (i);
			stack_a = stack_a->next;
			i++;
		}
	}
	return (-1);
}

/* int	get_pos_a(t_stack	*stack_a, int *dec, int step)
{
	int		i;

	if (!stack_a)
		return (-1);
	i = 0;
	while (stack_a)
	{
		if (get_unit(stack_a->index, step) == *dec)
		{
			return (i);
		}
		stack_a = stack_a->next;
		i++;
	}
	return (-1);
} */

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

int	push_min_b(t_stack **stack_b, t_stack **stack_a, int *dec, int step)
{
	int	i;

	i = get_pos_a(*stack_a, dec, step);
	if (i == -1)
		return (0);
	if (i == 1)
		swap_a(&(*stack_a), 0);
	else if (i > 1)
	{
		if (i <= (lst_size(*stack_a) / 2))
		{
			while (i-- > 0)
				rotate_a(&(*stack_a), 0);
		}
		else
		{
			i = lst_size(*stack_a) - i;
			while (i-- > 0)
				reverse_rotate_a(&(*stack_a), 0);
		}
	}
	push_b(&(*stack_b), &(*stack_a));
	return (1);
}

int	push_max_a(t_stack **stack_a, t_stack **stack_b, int *dec, int step)
{
	int	i;

	i = get_pos_b(*stack_b, dec, step);
	if (i == -1)
		return (0);
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
	return (1);
}

void	sort_stack(t_stack	**stack_a, t_stack	**stack_b, int *step)
{
	int	dec;

	dec = 0;
	while (dec <= 9)
	{
		while (push_min_b(&(*stack_b), &(*stack_a), &dec, *step))
			;
		dec++;
	}
	dec = 9;
	*step = *step + 1;
	while (dec >= 0)
	{
		while (push_max_a(&(*stack_a), &(*stack_b), &dec, *step))
			;
		dec--;
	}
	*step = *step + 1;
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
			return(printf("Error\n"), 1);
	i = 1;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (ft_atol(argv[i]) == ft_atol(argv[j]))
				return(printf("Error\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char	**argv)
{
	int		i;
	int		step;
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_stack	*tmp;

	if (ft_error(argc, argv))
		return(-1);
	step = 1;
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
		return(printf("Error\n"), 1);
	sort_stack(&stack_a, &stack_b, &step);
	sort_stack(&stack_a, &stack_b, &step);
	return (lst_clear(&stack_a), lst_clear(&stack_b), 0);
}
