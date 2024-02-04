/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:08:18 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/04 18:52:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_stack
{
	int				index;
	int				number;
	struct s_stack	*next;
}					t_stack;

long	ft_atol(const char *str);
int		sorted(t_stack *stack_a);
int		ft_error(int argc, char **argv);
int		get_pos_min(t_stack *stack_a);
int		get_pos_max(t_stack *stack_b);
t_stack	*new_node(int number);
t_stack	*lst_last(t_stack *lst);
void	lst_add_back(t_stack **lst, t_stack *new);
void	lst_clear(t_stack **lst);
int		lst_size(t_stack *lst);
void	swap_a(t_stack **stack_a);
void	swap_b(t_stack **stack_b);
void	swap_a_(t_stack **stack_a_);
void	swap_b_(t_stack **stack_b_);
void	swap_a_b(t_stack **stack_a, t_stack **stack_b);
void	push_a(t_stack **stack_a, t_stack **stack_b);
void	push_b(t_stack **stack_b, t_stack **stack_a);
void	rotate_a(t_stack **stack_a);
void	rotate_b(t_stack **stack_b);
void	rotate_a_(t_stack **stack_a_);
void	rotate_b_(t_stack **stack_b_);
void	rotate_a_b(t_stack **stack_a, t_stack **stack_b);
void	reverse_rotate_a(t_stack **stack_a);
void	reverse_rotate_b(t_stack **stack_b);
void	reverse_rotate_a_(t_stack **stack_a);
void	reverse_rotate_b_(t_stack **stack_b);
void	reverse_rotate_a_b(t_stack **stack_a, t_stack **stack_b);